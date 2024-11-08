#include "users.h"
#include <memory>
#include <mariadb/conncpp.hpp>
#include "create_user_request.h"
#include "../../Helpers/Cryptography/hash.h"

namespace Controllers
{
    void createUser(const std::unique_ptr<sql::Connection> &conn, const Requests::CreateUserRequest &user)
    {
        std::unique_ptr<sql::PreparedStatement> statement(
            conn->prepareStatement(
                "INSERT INTO users (first_name, last_name, email, password_hash, permission_level) VALUES (?, ?, ?, ?, ?)"
            )
        );

        statement->setString(1, user.first_name);
        statement->setString(2, user.last_name);
        statement->setString(3, user.email);
        statement->setString(4, Hash::hash(user.password, user.email));
        statement->setString(5, user.permissions_level);

        statement->executeUpdate();
    }
}