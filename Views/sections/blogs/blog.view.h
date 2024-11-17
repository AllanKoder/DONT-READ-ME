#ifndef BLOG_VIEW_H
#define BLOG_VIEW_H

#include "../../views.h"
#include <vector>
#include <cgicc/Cgicc.h>
#include "../../../Helpers/Database/Blogs/blog_dto.h"

namespace Views
{
    class Blog : public View
    {
    public:
        Blog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post);
    };
}

#endif