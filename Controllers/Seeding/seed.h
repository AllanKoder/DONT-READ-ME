#ifndef SEED_CONTROLLER_H
#define SEED_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Helpers/Database/Users/user_dto.h"
#include "../../Views/views.h"

namespace Controllers
{
    /**
     * @brief Function for seeding the database with sample users
     *
     * Creates admin, and two users.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @returns View the view for seeding the database.
     */
    Views::View seed(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
