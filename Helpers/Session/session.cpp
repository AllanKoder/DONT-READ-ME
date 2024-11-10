#include "session.h"
#include "../Cryptography/hash.h"
#include "../Database/db_connection.h"
#include "../Logger/logger.h"
#include "../../env.h"

namespace Session
{
    std::string createSessionToken(int userId)
    {
    }

    bool attempt(std::string username, std::string password)
    {
        auto connection = Database::GetConnection();

        // Get the password
        std::string password = Hash::hash(password, username);

        // Create a Statement
        std::shared_ptr<sql::Statement> stmnt(connection->createStatement());

        try
        {
            // Execute SELECT Statement
            std::unique_ptr<sql::ResultSet> res(
                stmnt->executeQuery("SELECT id FROM users WHERE username = ? AND password_hash = ?"));

            // Check if length == 1 
        }

        // Catch Exception
        catch (sql::SQLException &e)
        {
            std::string output = "Cannot check username and password ";
            output += e.what();
            Logger::logCritical(output);
        }
    }

    bool isValidToken(cgicc::CgiEnvironment environment);

}