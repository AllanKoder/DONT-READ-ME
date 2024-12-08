#ifndef CREATE_BLOG_VIEW_H
#define CREATE_BLOG_VIEW_H

#include <cgicc/Cgicc.h>
#include "../../views.h"

namespace Views
{
    /**
     * @brief A class representing the Create Blog view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a form that allows users to create a new blog post.
     */
    class CreateBlog : public View
    {
    public:
        /**
         * @brief Constructor for the CreateBlog class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        CreateBlog(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif