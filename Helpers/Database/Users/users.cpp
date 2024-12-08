#include "users.h"
#include <mariadb/conncpp.hpp>
#include "user_dto.h"
#include "../db_connection.h"
#include "../../Cryptography/crypto.h"

namespace Database
{
    void createUser(const Requests::CreateUserRequest &user)
    {
        auto connection = Database::GetConnection();

        // Create user statement
        std::unique_ptr<sql::PreparedStatement> statement(
            connection->prepareStatement(
                "INSERT INTO users (username, email, password_hash, permission_level) VALUES (?, ?, ?, ?)"));

        statement->setString(1, user.username);
        statement->setString(2, user.email);
        statement->setString(3, Crypto::hash(user.password, user.email));
        statement->setString(4, user.permissions_level);

        statement->executeUpdate();

        connection->close();
    }
}