#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Views/views.h"

namespace Controllers
{
    Views::View loginPost(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View logoutPost(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View loginPage(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
