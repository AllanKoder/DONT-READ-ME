#ifndef CREATE_BLOG_VIEW_H
#define CREATE_BLOG_VIEW_H

#include "../../views.h"
#include <cgicc/Cgicc.h>
#include <memory>

namespace Views
{
    class CreateBlog : public View
    {
    public:
        CreateBlog(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif 