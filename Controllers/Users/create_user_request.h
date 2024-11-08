#ifndef CREATE_USER_REQUEST_H
#define CREATE_USER_REQUEST_H

#include "../../config.h"

namespace Controllers::Requests
{
    class CreateUserRequest {
    public:
        CreateUserRequest(
            std::string username,
            std::string email,
            std::string password,
            std::string permissions_level
        ) : username(std::move(username)),
            email(std::move(email)),
            password(std::move(password)),
            permissions_level(std::move(permissions_level)) {}

        std::string username;
        std::string email;
        std::string password;
        std::string permissions_level;
    };
}
#endif
