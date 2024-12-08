#include <mariadb/conncpp.hpp>

namespace Database
{
    /**
     * @brief Establishes and returns a unique pointer to a database connection.
     *
     * This function creates a connection to the MariaDB database using the
     * MariaDB Connector/C++ and returns a unique pointer to the connection object.
     *
     * @return std::unique_ptr<sql::Connection> A unique pointer to the established database connection.
     */
    std::unique_ptr<sql::Connection> GetConnection();
}