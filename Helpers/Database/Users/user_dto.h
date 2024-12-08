#ifndef USER_DTO_H
#define USER_DTO_H

#include "../../../config.h"

namespace Database::Requests
{
    /**
     * @brief Class representing a request to create a new user.
     * 
     * This class encapsulates the necessary information required to create a new user
     * in the database, including the username, email, password, and permissions level.
     */
    class CreateUserRequest {
    public:
        /**
         * @brief Constructor for the CreateUserRequest class.
         * 
         * @param username The username of the new user.
         * @param email The email address of the new user.
         * @param password The password for the new user.
         * @param permissions_level The permissions level assigned to the new user (e.g., admin, user).
         */
        CreateUserRequest(
            std::string username,
            std::string email,
            std::string password,
            std::string permissions_level
        ) : username(std::move(username)),
            email(std::move(email)),
            password(std::move(password)),
            permissions_level(std::move(permissions_level)) {}

        std::string username;           // The username of the new user.
        std::string email;              // The email address of the new user.
        std::string password;           // The password for the new user.
        std::string permissions_level;  // The permissions level assigned to the new user.
    };
}
#endif