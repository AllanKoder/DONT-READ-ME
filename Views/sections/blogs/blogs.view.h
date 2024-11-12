#ifndef BLOGS_VIEW_H
#define BLOGS_VIEW_H

#include "../../views.h" 
#include <cgicc/Cgicc.h>

namespace Views
{
    class Blogs : public View 
    {
    public:
        Blogs(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif