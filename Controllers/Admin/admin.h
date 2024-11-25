#ifndef BLOG_CONTROLLER_H
#define BLOG_CONTROLLER_H

#include <memory>
#include "../../Views/views.h"

namespace Controllers
{
    Views::View createUserPage(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View createUserPost(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
