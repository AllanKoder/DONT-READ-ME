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

    // MFA2
    // Email
    Views::View emailCodePage(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View emailCodePost(std::shared_ptr<cgicc::Cgicc> cgi);
    // App
    Views::View appCodePage(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View appCodePost(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
