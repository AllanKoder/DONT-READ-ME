#ifndef BLOG_VIEW_H
#define BLOG_VIEW_H

#include "../../views.h"
#include <vector>
#include <cgicc/Cgicc.h>

namespace Views
{
    class CreateUser : public View
    {
    public:
        CreateUser(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif