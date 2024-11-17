#ifndef BLOG_CONTROLLER_H
#define BLOG_CONTROLLER_H

#include <memory>
#include "../../Views/views.h"

namespace Controllers
{
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi);
    Views::View createBlogPage(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
