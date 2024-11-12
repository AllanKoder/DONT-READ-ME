#ifndef BLOG_CONTROLLER_H
#define BLOG_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Views/views.h"

namespace Controllers
{
    Views::View blogsPage();
}

#endif
