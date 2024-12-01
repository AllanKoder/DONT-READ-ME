#include "session.h"
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"
#include "../Email/email.h"
#include "../Cryptography/crypto.h"
#include "../Request/request.h"
#include "../String/string_helpers.h"
#include "../Database/db_connection.h"
#include <array>
#include <memory>

namespace Session
{
    PrivilegeLevel stringToPrivilegeLevel(const std::string &levelStr)
    {
        if (levelStr == "admin")
        {
            return ADMIN;
        }
        else if (levelStr == "user")
        {
            return USER;
        }
        return USER;
    }

    std::optional<std::string> getCookieToken(std::shared_ptr<cgicc::Cgicc> cgi, std::string cookieName)
    {
        const std::vector<cgicc::HTTPCookie> cookiesList = cgi->getEnvironment().getCookieList();
        // check if there is token,
        // Search for the cookieName
        for (auto cookie : cookiesList)
        {
            if (cookie.getName() == cookieName)
            {
                return cookie.getValue();
            }
        }

        return std::nullopt;
    }

    // Function to retrieve the user ID from the SESSION_TOKEN cookie
    std::optional<UserInfo> userInfo(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<std::string> token = getCookieToken(cgi, "SESSION_TOKEN");

        if (!token.has_value())
        {
            Logger::logWarning("There is no session token");
            return std::nullopt;
        }

        // 1. Check the token is not modified
        // 2. Check if the token is in the database
        // 3. Check if the token is expired

        Logger::logInfo("checking valid token on: " + token.value());

        // Check if the token has the correct length
        if (token.value().length() != SESSION_TOKEN_SIZE)
        {
            Logger::logWarning("token is invalid size");
            return std::nullopt;
        }

        // Check if the token is in the database
        auto connection = Database::GetConnection(); // Get a database connection

        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT TIMESTAMPDIFF(SECOND, last_accessed, CURRENT_TIMESTAMP()) as time_difference, \
            st.user_id, \
            u.permission_level \
            FROM session_tokens st \
            JOIN users u ON st.user_id = u.id \
            WHERE st.value = ?;"));

        selectStatement->setString(1, token.value());

        try
        {
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());

            if (res->next())
            {
                int timeDiff = res->getInt("time_difference");

                if (timeDiff >= TOKEN_EXPIRY_TIME)
                {
                    // Has expired
                    Logger::logInfo("The token has expired. The timeDiff was " + std::to_string(timeDiff) + " with an expected timeDiff of at most " + std::to_string(TOKEN_EXPIRY_TIME));
                    return std::nullopt;
                }
                int userId = res->getInt("user_id"); // Get user ID from result set
                PrivilegeLevel level = stringToPrivilegeLevel(res->getString("permission_level").c_str());

                UserInfo info;
                info.id = userId;
                info.privilegeLevel = level;

                Logger::logInfo("Got the user_id: " + std::to_string(userId));
                connection->close();
                return info;
            }
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot fetch the user Token ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }

        Logger::logWarning("No token found for cookie");
        connection->close();
        return std::nullopt; // No Cookie found
    }

    bool deleteSessionToken(int userId)
    {
        // Delete all existing tokens with the user
        auto connection = Database::GetConnection(); // Get a database connection

        // Search for existing session token for this user
        std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
            "DELETE FROM session_tokens WHERE user_id = ?"));

        deleteStatement->setInt(1, userId);

        try
        {
            // Deleted
            deleteStatement->executeQuery();
        }
        catch (const sql::SQLException &e)
        {
            std::string output = "Could not delete existing tokens ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return false;
        }
        return true;
    }

    bool deletePendingSessionToken(int userId)
    {
        // Delete all existing tokens with the user
        auto connection = Database::GetConnection(); // Get a database connection

        // Search for existing session token for this user
        std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
            "DELETE FROM pending_session_tokens WHERE user_id = ?"));

        deleteStatement->setInt(1, userId);

        try
        {
            // Deleted
            deleteStatement->executeQuery();
        }
        catch (const sql::SQLException &e)
        {
            std::string output = "Could not delete existing pending session tokens";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return false;
        }
        return true;
    }

    // if the user is not logged in at all, then create the pending session token for the email stage
    // the user has logged in, did the email code, now create the app code token
    std::optional<std::string> createPendingSessionToken(int userId, std::string stage, std::string code = "")
    {
        if (!(stage == "email" || stage == "app"))
        {
            Logger::logInfo("Stage is not 'email' or 'app'");
            return std::nullopt;
        }

        if (!deletePendingSessionToken(userId))
        {
            Logger::logInfo("Could not delete old pending session tokens");
            return std::nullopt;
        }

        std::string token = Crypto::getRandomToken();

        Logger::logInfo("code is: " + code);
        Logger::logInfo("token is: " + token);
        auto connection = Database::GetConnection(); // Get a database connection
        // Create the token in the database
        std::shared_ptr<sql::PreparedStatement> insertStatement(connection->prepareStatement(
            "INSERT INTO pending_session_tokens (token, value, user_id, verification_type) VALUES(?, ?, ?, ?)"));

        // token, created time, value, user_id, stage
        insertStatement->setString(1, token);
        insertStatement->setString(2, code);
        insertStatement->setInt(3, userId);
        insertStatement->setString(4, stage);

        try
        {
            std::unique_ptr<sql::ResultSet> res(insertStatement->executeQuery());

            Logger::logInfo("Can execute query insert pending_session_tokens");

            // Pending Session Token Created
            connection->close();
            return token;
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot create pending_session_tokens:";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return empty on exception
        }

        // Failed, should not reach here
        return std::nullopt;
    }

    // Function to create a session token for a given user ID
    std::optional<std::string> createSessionToken(int userId)
    {
        if (!deleteSessionToken(userId))
        {
            Logger::logInfo("Could not delete old session tokens");
            return std::nullopt;
        }

        std::string token = Crypto::getRandomToken();

        auto connection = Database::GetConnection(); // Get a database connection
        // Create the token in the database
        std::shared_ptr<sql::PreparedStatement> insertStatement(connection->prepareStatement(
            "INSERT INTO session_tokens VALUES(?, CURRENT_TIMESTAMP(), ?)"));

        // last accessed is the current timestamp. NOW()
        // user id is the parameter
        insertStatement->setString(1, token);
        insertStatement->setInt(2, userId);

        try
        {
            std::unique_ptr<sql::ResultSet> res(insertStatement->executeQuery());

            Logger::logInfo("Can execute query insert session_token");

            // Session Token Created
            connection->close();
            return token;
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot create session_token:";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return empty on exception
        }

        // Failed, should not reach here
        return std::nullopt;
    }

    // Function to log in a user with email and password
    // will get rid of their old session_token
    std::optional<LoginResult> login(std::string email, std::string password)
    {
        Logger::logInfo("Reached login() function");

        // Check if the user is already logged in, if so, then, skip this.

        auto connection = Database::GetConnection(); // Get a database connection

        // Hash the password using Crypto with email as salt
        std::string hashedPassword = Crypto::hash(password, email);

        // Prepare an SQL statement to check if email and password hash match
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT id FROM users WHERE email = ? AND password_hash = ?"));

        selectStatement->setString(1, email);
        selectStatement->setString(2, hashedPassword);

        Logger::logInfo("email: " + email + " hashed password: " + hashedPassword);

        try
        {
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());

            // Is a valid email and password
            if (res->next())
            {
                int userId = res->getInt("id"); // Get user ID from result set

                Logger::logInfo("user id: " + userId);
                // Create a pending session token for this user ID
                // Send an email with the code, and create the pending session token

                // The code the user will input
                std::string sixCharCode = Crypto::getRandomSixCharCode();
                // Make the token
                std::optional<std::string> token = createPendingSessionToken(userId, "email", sixCharCode);

                if (token.has_value())
                {
                    // Send the email
                    Email::EmailMessage message;
                    message.to = email;
                    message.body = "This is your code: " + sixCharCode;
                    message.subject = "Don't README - Code";

                    Email::sendEmail(message);

                    connection->close();
                    // Login successful
                    LoginResult result;
                    result.isSessionToken = false;
                    result.pendingSessionToken = token.value();
                    return result;
                }
            }

            Logger::logWarning("Cannot find the user and password given");
            connection->close();
            return std::nullopt; // Login failed: no matching email/password found
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot check email and password: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }
    }

    std::optional<LoginResult> confirmEmailCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string userProvidedCode)
    {
        Logger::logInfo("Reached confirmEmailCode() function");

        // check if the user's cookie token is in the database.
        // Then, check if the code is a match.
        // Check if if it is expired
        // If the code is incorrect, then increment attempts, if we surpass the limit ()
        auto connection = Database::GetConnection(); // Get a database connection

        // Prepare an SQL statement to check if email and password hash match
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT TIMESTAMPDIFF(SECOND, created_time, CURRENT_TIMESTAMP()) as time_difference, \
                pt.value, \
                pt.verification_type, \
                u.permission_level, \
                u.id, \
                pt.attempts \
                FROM pending_session_tokens pt \
                JOIN users u ON pt.user_id = u.id \
                WHERE token = ?"));

        std::optional<std::string> userProvidedToken = getCookieToken(cgi, "PENDING_SESSION_TOKEN");
        if (!userProvidedToken.has_value())
        {
            Logger::logWarning("No provided token");
        }
        Logger::logInfo("User provided token: " + userProvidedToken.value());

        selectStatement->setString(1, userProvidedToken.value());

        try
        {
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());

            // Is a valid token
            if (res->next())
            {
                int timeDifference = res->getInt("time_difference"); // Get user ID from result set
                std::string value = res->getString("value").c_str();
                PrivilegeLevel level = stringToPrivilegeLevel(res->getString("permission_level").c_str());
                int userId = res->getInt("id");
                int attempts = res->getInt("attempts");

                // Statement to delete the token on either success or fail
                std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
                    "DELETE FROM pending_session_tokens WHERE token = ?"));
                deleteStatement->setString(1, userProvidedToken.value());

                if (value != userProvidedCode)
                {
                    Logger::logWarning("Invalid user code provided");

                    attempts++;
                    if (attempts >= MAX_CODE_ATTEMPTS)
                    {
                        Logger::logWarning("Maximum attempts reached for token: " + userProvidedToken.value());
                        // Delete the token
                        deleteStatement->executeUpdate();
                        Logger::logInfo("Token deleted due to max attempts: " + userProvidedToken.value());
                        return std::nullopt;
                    }

                    // Increment the attempts
                    std::shared_ptr<sql::PreparedStatement> updateStatement(connection->prepareStatement(
                        "UPDATE pending_session_tokens SET attempts = ? WHERE token = ?"));
                    updateStatement->setInt(1, attempts);
                    updateStatement->setString(2, userProvidedToken.value());
                    updateStatement->executeUpdate();

                    return std::nullopt;
                }

                if (timeDifference >= PENDING_TOKEN_EXPIRY_TIME)
                {
                    Logger::logWarning("Token has exceeded the expiry time");
                    // Delete expired token
                    deleteStatement->executeUpdate();
                    Logger::logInfo("Expired token deleted: " + userProvidedToken.value());
                    return std::nullopt;
                }

                Logger::logInfo("Code verified successfully");

                // Delete the token after successful verification
                deleteStatement->executeUpdate();
                Logger::logInfo("Token deleted after successful verification: " + userProvidedToken.value());

                // The user has succeeded, the code is valid.
                // If the privellege level is only user, they are validated now
                if (level == PrivilegeLevel::USER)
                {
                    std::optional<std::string> sessionToken = createSessionToken(userId);
                    if (!sessionToken.has_value())
                    {
                        return std::nullopt;
                    }

                    LoginResult result;
                    result.isSessionToken = true;
                    result.sessionToken = sessionToken.value();
                    return result;
                }
                // the admin needs to do the next step of using the auth app
                else if (level == PrivilegeLevel::ADMIN)
                {
                    std::optional<std::string> pendingSessionToken = createPendingSessionToken(userId, "app");
                    if (!pendingSessionToken.has_value())
                    {
                        return std::nullopt;
                    }

                    LoginResult result;
                    result.isSessionToken = false;
                    result.pendingSessionToken = pendingSessionToken.value();
                    return result;
                }
            }

            Logger::logWarning("Cannot find the session token given");
            connection->close();
            return std::nullopt; // Login failed: no matching email/password found
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot confirm the email code: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }
    }

    std::string getCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        // Hash it, using the Crypto::hash
        std::optional<std::string> token = getCookieToken(cgi, "SESSION_TOKEN");
        if (!token.has_value())
        {
            return "This is invalid!!!! You should be logged in. This code will never be reached";
        }

        return Crypto::hash(token.value(), CRSF_KEY);
    }

    bool isValidPassword(std::string password)
    {
        // simple policy, just check length
        return password.length() >= 6;
    }

    bool isValidCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        // Get the session token
        std::optional<std::string> token = getCookieToken(cgi, "SESSION_TOKEN");
        if (!token.has_value())
        {
            return false;
        }

        // Compare the user session token to the one in the post data
        std::string csrfToken = cgi->getElement("csrf_token")->getValue();
        // Check if the user has filled the CSRF token for posting
        if (csrfToken.empty())
        {
            Logger::logWarning("Invalid parameters for creating blog");
            return false;
        }

        // Is their sent token valid?
        return Crypto::hash(token.value(), CRSF_KEY) == csrfToken;
    }
}