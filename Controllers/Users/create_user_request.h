#ifndef CREATE_USER_REQUEST_H
#define CREATE_USER_REQUEST_H

#include "../../config.h"

namespace Controllers::Requests
{
    class CreateUserRequest {
    public:
        CreateUserRequest(
            std::string first_name,
            std::string last_name,
            std::string email,
            std::string password,
            std::string permissions_level
        ) : first_name(std::move(first_name)),
            last_name(std::move(last_name)),
            email(std::move(email)),
            password(std::move(password)),
            permissions_level(std::move(permissions_level)) {}

        std::string first_name;
        std::string last_name;
        std::string email;
        std::string password;
        std::string permissions_level;
    };
}
#endif
