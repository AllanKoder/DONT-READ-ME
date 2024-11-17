#ifndef BLOGS_VIEW_H
#define BLOGS_VIEW_H

#include "../../views.h"
#include <vector>
#include <cgicc/Cgicc.h>
#include "../../../Helpers/Database/Blogs/blog_dto.h"

namespace Views
{
    class Blogs : public View
    {
    public:
        Blogs(std::shared_ptr<cgicc::Cgicc> cgi, std::vector<Database::Requests::BlogModel>);
    };
}

#endif