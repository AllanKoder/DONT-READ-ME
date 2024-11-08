#include "db_connection.h"
#include "../../env.h"
namespace Database
{
    std::unique_ptr<sql::Connection> GetConnection()
    {
        // Seed the database with users
        // Instantiate Driver
        sql::Driver *driver = sql::mariadb::get_driver_instance();

        // Configure Connection
        sql::SQLString url("jdbc:mariadb://localhost:3306/blog");

        // Use a properties map for the other connection options
        sql::Properties properties({
            {"user", DATABASE_USERNAME},
            {"password", DATABASE_PASSWORD},
        });

        // Establish Connection
        // Use a smart pointer for extra safety
        std::unique_ptr<sql::Connection> connection(driver->connect(url, properties));

        return connection;
    }
}