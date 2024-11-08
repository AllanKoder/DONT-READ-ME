#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Controllers/Users/users.h"

void seed()
{
    try
    {
        // Seed the database with users
        // Instantiate Driver
        sql::Driver *driver = sql::mariadb::get_driver_instance();

        // Configure Connection
        sql::SQLString url("jdbc:mariadb://localhost:3306/blog");

        // Use a properties map for the other connection options
        sql::Properties properties({
            {"user", "admin"},
            {"password", "admin"},
        });

        // Establish Connection
        // Use a smart pointer for extra safety
        std::unique_ptr<sql::Connection> connection(driver->connect(url, properties));

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
    // Output HTTP headers for HTML
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;

    // Start HTML document
    std::cout << cgicc::html().set("lang", "en") << std::endl;
    std::cout << cgicc::head() << cgicc::title("Hello World") << cgicc::head() << std::endl;
    std::cout << cgicc::body() << std::endl;

    // Print seeded
    seed();
    std::cout << "Seeded.\n";

    // End HTML document
    std::cout << cgicc::body() << cgicc::html() << std::endl;

    return 0;
}
