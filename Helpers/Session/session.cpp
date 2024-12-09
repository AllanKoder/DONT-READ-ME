#include "session.h"
#include <array>
#include <memory>
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"
#include "../Email/email.h"
#include "../Cryptography/crypto.h"
#include "../Request/request.h"
#include "../String/string_helpers.h"
#include "../Database/db_connection.h"

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
        // Check if there is token, search for the cookieName
        for (auto cookie : cookiesList)
        {
            if (cookie.getName() == cookieName)
            {
                if (!cookie.getValue().empty())
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

        // 1. Check if the token is in the database
        // 2. Check if the token is expired
        // 3. Reset the last accessed timer
        // 4. Give the user info

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
            u.username, \
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
                std::string username = res->getString("username").c_str();
                int userId = res->getInt("user_id"); // Get user ID from result set
                PrivilegeLevel level = stringToPrivilegeLevel(res->getString("permission_level").c_str());

                Logger::logInfo("Time difference is: " + std::to_string(timeDiff) + ". The expiry time is: " + std::to_string(TOKEN_EXPIRY_TIME));
                if (timeDiff >= TOKEN_EXPIRY_TIME)
                {
                    // Has expired
                    Logger::logInfo("The token has expired. The timeDiff was " + std::to_string(timeDiff) + " with an expected timeDiff of at most " + std::to_string(TOKEN_EXPIRY_TIME));
                    deleteSessionToken(userId);
                    return std::nullopt;
                }

                // Update last_accessed timestamp
                std::shared_ptr<sql::PreparedStatement> updateStatement(connection->prepareStatement(
                    "UPDATE session_tokens SET last_accessed = CURRENT_TIMESTAMP() WHERE value = ?;"));
                updateStatement->setString(1, token.value());
                updateStatement->executeUpdate();

                // returned User info
                UserInfo info;
                info.id = userId;
                info.privilegeLevel = level;
                info.username = username;

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
            return std::nullopt; // Return nullopt on exception
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
    std::optional<std::string> createPendingSessionToken(int userId, std::string stage, std::string code)
    {
        if (!(stage == "email" || stage == "app"))
        {
            Logger::logInfo("Stage is not 'email' or 'app'");
            return std::nullopt;
        }

        // Delete the old pending session tokens
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

        // token, value, user_id, stage
        insertStatement->setString(1, token);
        insertStatement->setString(2, code);
        insertStatement->setInt(3, userId);
        insertStatement->setString(4, stage);

        try
        {
            // Create the pending token
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

    std::optional<std::string> createSessionToken(int userId)
    {
        // Ensure the previous token with the user is dissolved
        if (!deleteSessionToken(userId))
        {
            Logger::logInfo("Could not delete old session tokens");
            return std::nullopt;
        }

        auto connection = Database::GetConnection(); // Get a database connection

        // Create the token in the database
        std::shared_ptr<sql::PreparedStatement> insertStatement(connection->prepareStatement(
            "INSERT INTO session_tokens (value, user_id) VALUES(?, ?)"));

        std::string token = Crypto::getRandomToken();
        insertStatement->setString(1, token);
        insertStatement->setInt(2, userId);

        try
        {
            // Perform the insert command
            insertStatement->executeQuery();
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

    std::optional<LoginResult> login(std::string email, std::string password)
    {
        Logger::logInfo("Reached login() function");

        auto connection = Database::GetConnection(); // Get a database connection

        // Hash the password using Crypto with email and salt
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

            // Is a valid email and password, that is in the database
            if (res->next())
            {
                int userId = res->getInt("id"); // Get user ID from result set
                Logger::logInfo("user id that is logging in: " + userId);

                // Create a pending session token for this user ID
                // Send an email with the code, and create the pending session token

                // The code the user will input from email
                std::string sixCharCode = Crypto::getRandomSixCharCode();
                // Make the pending session token, (user still needs to do MFA2)
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
            return std::nullopt; // Return nullopt on exception
        }
    }

    bool isValidPendingSessionToken(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        auto connection = Database::GetConnection(); // Get a database connection

        // Prepare an SQL statement to check if token exists
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT token FROM pending_session_tokens WHERE token = ?"));

        std::optional<std::string> userProvidedToken = getCookieToken(cgi, "PENDING_SESSION_TOKEN");
        if (!userProvidedToken.has_value())
        {
            Logger::logWarning("No provided token");
            return false;
        }
        Logger::logInfo("User provided token: " + userProvidedToken.value());

        selectStatement->setString(1, userProvidedToken.value());

        try
        {
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());
            // Is a token that exists
            if (res->next())
            {
                return true;
            }
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot select for token: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return false; // Return false on exception
        }

        // Should never reach here, but false anyhow
        return false;
    }

    std::optional<LoginResult> confirmEmailCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string userProvidedCode)
    {
        Logger::logInfo("Reached confirmEmailCode() function");

        // 1. Check if the user's cookie token is in the database.
        // 2. Then, check if the code is a match.
        // 3. Check if if it is expired, if so, delete it.
        // 4. If the code is incorrect, then increment attempts, if we surpass the limit.
        // 5. If the code is correct, check if the user is admin, if so, create the next step of authentication.
        // 6. If the code is correct and the user is not admin, create the session token for them.

        auto connection = Database::GetConnection(); // Get a database connection

        // Prepare an SQL statement to check if token exists, with user information included
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

        // Get the user provided token in their session
        std::optional<std::string> userProvidedToken = getCookieToken(cgi, "PENDING_SESSION_TOKEN");
        if (!userProvidedToken.has_value())
        {
            Logger::logWarning("No provided token");
            return std::nullopt;
        }

        Logger::logInfo("User provided token: " + userProvidedToken.value());

        selectStatement->setString(1, userProvidedToken.value());

        try
        {
            // Execute the selection query
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());

            // Is a valid token
            if (res->next())
            {
                int timeDifference = res->getInt("time_difference");
                std::string value = res->getString("value").c_str();
                PrivilegeLevel level = stringToPrivilegeLevel(res->getString("permission_level").c_str());
                int userId = res->getInt("id");
                int attempts = res->getInt("attempts");

                Logger::logInfo("Pending token expiry time is: " + std::to_string(PENDING_TOKEN_EXPIRY_TIME) + ". The current time difference is: " + std::to_string(timeDifference));
                
                // Statement to delete the token on either success or fail
                std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
                    "DELETE FROM pending_session_tokens WHERE token = ?"));
                deleteStatement->setString(1, userProvidedToken.value());

                if (timeDifference >= PENDING_TOKEN_EXPIRY_TIME)
                {
                    // Delete expired token
                    deleteStatement->executeUpdate();
                    Logger::logInfo("Expired token deleted: " + userProvidedToken.value());
                    return std::nullopt;
                }

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

                    // Return user session token
                    LoginResult result;
                    result.isSessionToken = true;
                    result.sessionToken = sessionToken.value();
                    return result;
                }
                // The admin needs to do the next step of using the auth app
                else if (level == PrivilegeLevel::ADMIN)
                {
                    // The code the challenge uses
                    std::string sixCharCode = Crypto::getRandomSixCharCode();

                    std::optional<std::string> pendingSessionToken = createPendingSessionToken(userId, "app", sixCharCode);
                    if (!pendingSessionToken.has_value())
                    {
                        return std::nullopt;
                    }

                    // Return admin pending session token
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

    std::optional<LoginResult> confirmAuthCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string userProvidedCode)
    {
        Logger::logInfo("Reached confirmAuthCode() function");

        // 1. Check if it exists in database
        // 2. Check if it is expired
        // 3. Check if the code matches (the challenge input with the expected digest)
        // 4. If it is wrong, increment attempts
        // 5, If it is correct, upgrade to a session token

        auto connection = Database::GetConnection(); // Get a database connection

        // Prepare an SQL statement to check if the token exists
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT TIMESTAMPDIFF(SECOND, created_time, CURRENT_TIMESTAMP()) as time_difference, \
                pt.verification_type, \
                pt.value, \
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
            return std::nullopt;
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
                PrivilegeLevel level = stringToPrivilegeLevel(res->getString("permission_level").c_str());
                int userId = res->getInt("id");
                int attempts = res->getInt("attempts");
                std::string challengeValue = res->getString("value").c_str();

                std::string value = Crypto::getAppCode(challengeValue);

                Logger::logInfo("The expected value is: " + value + ". Provided is: " + userProvidedCode);

                // Statement to delete the token on either success or fail
                std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
                    "DELETE FROM pending_session_tokens WHERE token = ?"));
                deleteStatement->setString(1, userProvidedToken.value());

                if (timeDifference >= PENDING_TOKEN_EXPIRY_TIME)
                {
                    Logger::logWarning("Token has exceeded the expiry time");
                    // Delete expired token
                    deleteStatement->executeUpdate();
                    Logger::logInfo("Expired token deleted: " + userProvidedToken.value());
                    return std::nullopt;
                }

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

                Logger::logInfo("Code verified successfully");

                // Delete the token after successful verification
                deleteStatement->executeUpdate();
                Logger::logInfo("Token deleted after successful verification: " + userProvidedToken.value());

                // The user has succeeded, the code is valid.
                // the admin can be logged in now
                if (level == PrivilegeLevel::ADMIN)
                {
                    // Create the session token
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
                else
                {
                    Logger::logCritical("User is not Admin in the pending session token, but logged in to here?");
                    return std::nullopt;
                }
            }

            Logger::logWarning("Cannot find the pending session token given");
            connection->close();
            return std::nullopt;
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot confirm the email code: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }
        return std::nullopt;
    }

    std::optional<std::string> getChallengeCode(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        // Get the value from the pending session token
        Logger::logInfo("Reached getChallengeCode() function");

        auto connection = Database::GetConnection(); // Get a database connection

        // Search for the challenge code for the pending_session_token
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT value FROM pending_session_tokens WHERE token = ?"));

        std::optional<std::string> userProvidedToken = getCookieToken(cgi, "PENDING_SESSION_TOKEN");
        if (!userProvidedToken.has_value())
        {
            Logger::logWarning("No provided token");
            return std::nullopt;
        }

        Logger::logInfo("User provided token: " + userProvidedToken.value());

        selectStatement->setString(1, userProvidedToken.value());

        try
        {
            std::unique_ptr<sql::ResultSet> res(selectStatement->executeQuery());

            // Is a valid token
            if (res->next())
            {
                std::string challengeValue = res->getString("value").c_str();
                // return the challenge value
                return challengeValue;
            }
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot get the challenge code: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }
        return std::nullopt;
    }

    std::string getCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<std::string> token = getCookieToken(cgi, "SESSION_TOKEN");
        if (!token.has_value())
        {
            return "This is invalid!!!! You should be logged in. This code will never be reached";
        }

        // Hash it with the secret key
        return Crypto::hash(token.value(), CRSF_KEY);
    }

    bool isValidPassword(std::string password)
    {
        // Simple policy, just check length
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

        // Check if their sent CSRF token is valid by comparing with the expected results with their session
        return Crypto::hash(token.value(), CRSF_KEY) == csrfToken;
    }
}