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
            // Create a user
            auto user = Database::Requests::CreateUserRequest(
                "user",
                "john.lennon@apple.com",
                "password",
                "user");

            Database::createUser(user);

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