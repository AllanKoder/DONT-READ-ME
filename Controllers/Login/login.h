#ifndef SEED_H
#define SEED_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Helpers/Database/Users/create_user_request.h"
#include "../../Views/views.h"

namespace Controllers
{
    Views::View loginPost();
    Views::View loginPage();
}

#endif
