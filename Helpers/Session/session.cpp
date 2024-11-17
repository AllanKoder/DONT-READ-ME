#include "session.h"
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"
#include "../Cryptography/crypto.h"
#include "../Database/db_connection.h"
#include <crypto++/rdrand.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <array>
#include <memory>

namespace Session
{
    std::optional<int> isValidAuthToken(std::string token)
    {
        // 1. Check the token is not modified
        // 2. Check if the token is in the database
        // 3. Check if the token is expired

        Logger::logInfo("checking valid token on: " + token);

        // Check if the token has the correct length
        if (token.length() != SESSION_TOKEN_SIZE) {
            return std::nullopt;
        }

        // Get the first (SESSION_TOKEN_SIZE - 64) characters (randomHex part)
        std::string randomHex = token.substr(0, SESSION_TOKEN_SIZE - 64);

        // Calculate the HMAC for the randomHex part
        std::string calculatedMacCode = Crypto::hmac(randomHex);

        // Extract the MAC code from the token (last 64 characters)
        std::string providedMacCode = token.substr(SESSION_TOKEN_SIZE - 64);

        // Compare the calculated MAC code with the provided one
        if (calculatedMacCode != providedMacCode)
        {
            Logger::logWarning("Session token has been tampered with");
            return std::nullopt;
        }

        // Check if the token is in the database
        auto connection = Database::GetConnection(); // Get a database connection
        
        std::shared_ptr<sql::PreparedStatement> selectStatement(connection->prepareStatement(
            "SELECT TIMESTAMPDIFF(SECOND, last_accessed, CURRENT_TIMESTAMP()) as time_difference, user_id FROM session_tokens WHERE value = ?")
        );

        selectStatement->setString(1, token);

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
                Logger::logInfo("Got the user_id: " + std::to_string(userId));
                connection->close();
                return userId;
            }
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot fetch the user Token";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }

        connection->close();
        return std::nullopt;
    }

    // Function to retrieve the user ID from the SESSION_TOKEN cookie
    std::optional<int> userId(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        const std::vector<cgicc::HTTPCookie> cookiesList = cgi->getEnvironment().getCookieList();
        // check if there is token,
        // Search for the cookie variable "SESSION_TOKEN"
        for (auto cookie : cookiesList)
        {
            if (cookie.getName() == "SESSION_TOKEN")
            {
                std::string token = cookie.getValue();
                std::optional<int> userId = isValidAuthToken(token);
                if (!userId.has_value())
                {
                    Logger::logInfo("Invalid session token");
                    return std::nullopt;
                }
                
                // The session_token is in the database
                return userId.value();
            }
        }

        return std::nullopt; // No Cookie found
    }

    bool deleteSessionToken(int userId)
    {
        // Delete all existing tokens with the user
        auto connection = Database::GetConnection(); // Get a database connection

        // Search for existing session token for this user
        std::shared_ptr<sql::PreparedStatement> deleteStatement(connection->prepareStatement(
            "DELETE FROM session_tokens WHERE user_id = ?"
            )
        );

        deleteStatement->setInt(1, userId);

        try
        {
            // Deleted
            deleteStatement->executeQuery();
        }
        catch(const sql::SQLException& e)
        {
            std::string output = "Could not delete existing tokens ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return false;
        }
        return true;
    }

    // Function to create a session token for a given user ID
    std::optional<std::string> createSessionToken(int userId)
    {
        if (!deleteSessionToken(userId))
        {
            Logger::logInfo("Could not delete old session tokens");
            return std::nullopt;
        }

        // Create a random token of length, use the SHA with a random input
        
        // Turn the SESSION_TOKEN_SIZE to the the byte length (which is smaller when converted to string again)
        // Subtract 64 since that is the length of the MAC code.
        const std::size_t tokenLength = (int)((SESSION_TOKEN_SIZE - 64)/2);

        // Turning to hex will make the size double
        std::array<CryptoPP::byte, tokenLength> randomBytes;

        // Use AutoSeededRandomPool for secure random number generation
        CryptoPP::AutoSeededRandomPool rng;
        rng.GenerateBlock(randomBytes.data(), randomBytes.size());

        // Convert random bytes to hex string
        std::string randomHex;
        CryptoPP::HexEncoder hexEncoder(new CryptoPP::StringSink(randomHex));
        hexEncoder.Put(randomBytes.data(), randomBytes.size());
        hexEncoder.MessageEnd();

        // Create the MAC code
        std::string macCode = Crypto::hmac(randomHex);

        Logger::logInfo("Generated randomHex:" + randomHex);
        Logger::logInfo("Generated macCode:" + macCode);
        std::string token = randomHex + macCode;
        Logger::logInfo("token:" + token);
        
        auto connection = Database::GetConnection(); // Get a database connection
        // Create the token in the database
        std::shared_ptr<sql::PreparedStatement> insertStatement(connection->prepareStatement(
            "INSERT INTO session_tokens VALUES(?, CURRENT_TIMESTAMP(), ?)")
        );

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
    std::optional<std::string> login(std::string email, std::string password)
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
                // Create a session token for this user ID
                std::optional<std::string> token = createSessionToken(userId);
                if (token.has_value())
                {
                    Logger::logInfo("Created Cookie: " + token.value());

                    connection->close();
                    // Login successful
                    return token;
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
}