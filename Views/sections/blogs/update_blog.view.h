#ifndef UPDATE_BLOG_VIEW_H
#define UPDATE_BLOG_VIEW_H

#include "../../views.h"
#include <cgicc/Cgicc.h>
#include "../../../Helpers/Database/Blogs/blog_dto.h"

#include <memory>

namespace Views
{
    class UpdateBlog : public View
    {
    public:
        UpdateBlog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post);
    };
}

#endif 