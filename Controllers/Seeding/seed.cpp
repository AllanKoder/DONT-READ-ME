#include "seed.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
#include "../../Helpers/Database/Users/users.h"
#include <iostream>

namespace Controllers
{
    Views::View seed(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        try
        {
            // Create user1
            auto user1 = Database::Requests::CreateUserRequest(
                "user",
                "john.lennon@apple.com",
                "password",
                "user");

            // Create user2
            auto user2 = Database::Requests::CreateUserRequest(
                "user32",
                "john112@apple.com",
                "password1",
                "user");

            Database::createUser(user1);
            Database::createUser(user2);

            Logger::logInfo("Successfully Seeded!");
        }
        catch (sql::SQLException &e)
        {
            std::cerr << e.what() << '\n';
            Logger::logWarning(e.what());
        }    

        return Views::Seed(cgi);
    }
}