#include "session.h"
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"
#include "../Cryptography/crypto.h"
#include "../Database/db_connection.h"
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPCookie.h>

namespace Session
{
    // Function to retrieve the user ID from the SESSION_TOKEN cookie
    std::optional<int> userId()
    {
        cgicc::Cgicc cgi;
        cgi.getEnvironment().getCookieList();
        // check if there is token,
        // Search for the cookie variable "SESSION_TOKEN"

        // 
    }

    // Function to create a session token for a given user ID
    std::string createSessionToken(int userId)
    {
        // Create a random token of length
        int tokenLength = SESSION_TOKEN_SIZE - 32;
        // Use 
        // Crypto::hmac(); 
        // to create a MAC code
        // which is of length 32
        
        // append it together, store it as the token value
        // last accessed is the current timestamp
        // user id is the parameter

        
        // return the token
        return "TestToken";
    }

    // Function to log in a user with username and password
    bool login(std::string username, std::string password)
    {
        Logger::logInfo("Reached login() function");

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
            
            Logger::logCritical("Can execute query");

            if (res->next())
            {
                int userId = res->getInt("id"); // Get user ID from result set

                Logger::logCritical("user id: " + userId);

                // Create a session token for this user ID
                std::string token = createSessionToken(userId);

                // Set the SESSION_TOKEN cookie with the generated token
                cgicc::HTTPCookie cookie("SESSION_TOKEN", token);
                // Set cookie expiration to 1 hour
                cookie.setMaxAge(3600); 
                // Set path for which this cookie is valid
                cookie.setPath("/");

                Logger::logInfo("Created Cookie: " + token);

                connection->close();
                // Login successful
                return true; 
            }
            
            connection->close();
            return false; // Login failed: no matching username/password found
        }
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot check username and password: ";
            output += e.what(); // Log any SQL exceptions that occur during execution
            Logger::logCritical(output);
            connection->close();
            return false; // Return false on exception
        }
    }
}