#include "session.h"
#include "../Cryptography/crypto.h"
#include "../Database/db_connection.h"
#include "../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"

namespace Session
{

    std::optional<int> userId()
    {
        cgicc::Cgicc cgi;
        cgi.getEnvironment().getCookieList();

        // check if there is token,
        // Search for the cookie variable "SESSION_TOKEN"

        // 
    }

    std::string createSessionToken(int userId)
    {
        // Create a random token of length
        int tokenLength = SESSION_TOKEN_SIZE - 32;
        // Use 
        Crypto::hmac(); 
        // to create a MAC code
        // which is of length 32
        
        // append it together, store it as the token value
        // last accessed is the current timestamp
        // user id is the parameter
        
        
        // return the token
    }

    bool login(std::string username, std::string password)
    {
        auto connection = Database::GetConnection();

        // Get the password
        std::string password = Crypto::hash(password, username);

        // Create a Statement
        std::shared_ptr<sql::Statement> stmnt(connection->createStatement());

        try
        {
            // Execute SELECT Statement
            std::unique_ptr<sql::ResultSet> res(
                stmnt->executeQuery("SELECT id FROM users WHERE username = ? AND password_hash = ?"));

            // Check if length == 1 

            // If it is 1, then there is a token, return it

            // If not, generate a  token

            return createSessionToken();            
        }

        // Catch Exception
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot check username and password ";
            output += e.what();
            Logger::logCritical(output);
        }
    }
}