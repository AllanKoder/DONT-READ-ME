#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Controllers/Users/users.h"
#include "../../Views/layout/app.view.h"
#include "../../Helpers/Database/db_connection.h"

void seed()
{
    try
    {
        auto connection = Database::GetConnection();
        // Create a user
        auto user = Controllers::Requests::CreateUserRequest(
            "John",
            "Lennon",
            "john.lennon@apple.com",
            "password",
            "user");
        Controllers::createUser(connection, user);

        connection->close();

        Logger::logInfo("Successfully Seeded!");
    }
    catch (sql::SQLException &e)
    {
        std::cerr << e.what() << '\n';
        Logger::logWarning(e.what());
    }
}

int main()
{
    Views::AppLayoutStart();

    // Print seeded
    seed();
    std::cout << "Seeded.\n";

    Views::AppLayoutEnd();
    return 0;
}
