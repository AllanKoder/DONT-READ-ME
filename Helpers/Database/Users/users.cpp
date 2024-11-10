#include "users.h"
#include <memory>
#include <mariadb/conncpp.hpp>
#include "create_user_request.h"
#include "../../Cryptography/hash.h"
#include "../db_connection.h"

namespace Database
{
    void createUser(const Requests::CreateUserRequest &user)
    {
        auto connection = Database::GetConnection();

        std::unique_ptr<sql::PreparedStatement> statement(
            connection->prepareStatement(
                "INSERT INTO users (username, email, password_hash, permission_level) VALUES (?, ?, ?, ?)"
            )
        );

        statement->setString(1, user.username);
        statement->setString(3, user.email);
        statement->setString(4, Hash::hash(user.password, user.username));
        statement->setString(5, user.permissions_level);

        statement->executeUpdate();

        connection->close();
    }
}