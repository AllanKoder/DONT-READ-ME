#include <mariadb/conncpp.hpp>

namespace Database
{
    std::unique_ptr<sql::Connection> GetConnection();
}