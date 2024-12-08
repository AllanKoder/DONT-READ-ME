#ifndef USERS_H
#define USERS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "user_dto.h"

namespace Database
{
    /**
     * @brief Creates a new user in the database.
     *
     * This function takes a CreateUserRequest object containing the necessary information
     * to create a new user and executes the corresponding SQL command to insert the user
     * into the database.
     *
     * @param user A constant reference to a CreateUserRequest object containing
     *              the details of the user to be created (username, email, password, permissions level).
     */
    void createUser(const Requests::CreateUserRequest &user);
}

#endif 