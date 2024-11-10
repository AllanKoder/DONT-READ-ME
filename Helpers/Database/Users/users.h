#ifndef USERS_H
#define USERS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "create_user_request.h"

namespace Database
{
    void createUser(const Requests::CreateUserRequest& user);
}

#endif
