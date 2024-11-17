#ifndef USERS_H
#define USERS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "user_dto.h"

namespace Database
{
    void createUser(const Requests::CreateUserRequest& user);
}

#endif
