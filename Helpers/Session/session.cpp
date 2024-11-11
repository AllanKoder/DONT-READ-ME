#include "session.h"
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"
#include "../Cryptography/crypto.h"
#include "../Database/db_connection.h"
#include <cgicc/Cgicc.h>
#include <crypto++/rdrand.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <array>

namespace Session
{
    bool isValidAuthToken(std::string token)
    {
        // Check if the token has the correct length
        if (token.length() != SESSION_TOKEN_SIZE) {
            return false;
        }

        // Get the first (SESSION_TOKEN_SIZE - 64) characters (randomHex part)
        std::string randomHex = token.substr(0, SESSION_TOKEN_SIZE - 64);

        // Calculate the HMAC for the randomHex part
        std::string calculatedMacCode = Crypto::hmac(randomHex);

        // Extract the MAC code from the token (last 64 characters)
        std::string providedMacCode = token.substr(SESSION_TOKEN_SIZE - 64);

        // Compare the calculated MAC code with the provided one
        return (calculatedMacCode == providedMacCode);
    }

    // Function to retrieve the user ID from the SESSION_TOKEN cookie
    std::optional<int> userId(const cgicc::Cgicc& cgi)
    {
        const std::vector<cgicc::HTTPCookie> cookiesList = cgi.getEnvironment().getCookieList();
        // check if there is token,
        // Search for the cookie variable "SESSION_TOKEN"
        for (auto cookie : cookiesList)
        {
            if (cookie.getName() == "SESSION_TOKEN")
            {
                std::string token = cookie.getValue();
                if (isValidAuthToken(token) == false)
                {
                    Logger::logInfo("Invalid session token, has been tampered");
                    return std::nullopt;
                }
                return 1;

                // Check if the 
            }
        }

        return std::nullopt; // No Cookie found
    }

    // Function to create a session token for a given user ID
    std::optional<std::string> createSessionToken(int userId)
    {
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

        // Create the token in the database
        auto connection = Database::GetConnection(); // Get a database connection
        
        std::shared_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(
            "INSERT INTO session_tokens VALUES(?, CURRENT_TIMESTAMP(), ?)")
        );

        // last accessed is the current timestamp. NOW()
        // user id is the parameter
        pstmt->setString(1, token);
        pstmt->setInt(2, userId);
        
        try
        {
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

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

    // Function to log in a user with username and password
    std::optional<std::string> login(std::string username, std::string password)
    {
        Logger::logInfo("Reached login() function");

        // Check if the user is already logged in, if so, then, skip this.

        auto connection = Database::GetConnection(); // Get a database connection

        // Hash the password using Crypto with username as salt
        std::string hashedPassword = Crypto::hash(password, username);

        // Prepare an SQL statement to check if username and password hash match
        std::shared_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(
            "SELECT id FROM users WHERE username = ? AND password_hash = ?"));

        pstmt->setString(1, username);
        pstmt->setString(2, hashedPassword);

        Logger::logInfo("username: " + username + " hashed password: " + hashedPassword);

        try
        {
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

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
            return std::nullopt; // Login failed: no matching username/password found
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot check username and password: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return std::nullopt; // Return false on exception
        }
    }
}