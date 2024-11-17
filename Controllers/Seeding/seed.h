#ifndef SEED_CONTROLLER_H
#define SEED_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Helpers/Database/Users/user_dto.h"
#include "../../Views/views.h"

namespace Controllers
{
    Views::View seed(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
