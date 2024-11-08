#ifndef USERS_H
#define USERS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "create_user_request.h"

namespace Controllers
{
    void createUser(const std::unique_ptr<sql::Connection>& connection, const Requests::CreateUserRequest& user);
}

#endif
