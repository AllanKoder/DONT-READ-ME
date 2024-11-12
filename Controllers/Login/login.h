#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Views/views.h"

namespace Controllers
{
    Views::View loginPost();
    Views::View loginPage();
}

#endif
