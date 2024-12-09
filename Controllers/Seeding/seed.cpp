#include "seed.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/String/string_helpers.h"
#include <iostream>

namespace Controllers
{
    Views::View seed(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        try
        {
            // Create admin
            auto admin = Database::Requests::CreateUserRequest(
                StringHelpers::sanitizeString("admin"),
                StringHelpers::sanitizeString("admin@admin.com"),
                "admin",
                "admin");

            // Create user1
            auto user1 = Database::Requests::CreateUserRequest(
                StringHelpers::sanitizeString("user"),
                StringHelpers::sanitizeString("john.lennon@apple.com"),
                "password",
                "user");

            // Create user2
            auto user2 = Database::Requests::CreateUserRequest(
                StringHelpers::sanitizeString("user32"),
                StringHelpers::sanitizeString("john112@apple.com"),
                "password1",
                "user");

            Database::createUser(admin);
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