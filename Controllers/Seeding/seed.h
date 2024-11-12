#ifndef SEED_CONTROLLER_H
#define SEED_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Helpers/Database/Users/create_user_request.h"
#include "../../Views/views.h"

namespace Controllers
{
    Views::View seed();
}

#endif
