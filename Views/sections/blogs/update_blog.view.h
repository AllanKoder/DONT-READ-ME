#ifndef UPDATE_BLOG_VIEW_H
#define UPDATE_BLOG_VIEW_H

#include <cgicc/Cgicc.h>
#include "../../views.h"
#include "../../../Helpers/Database/Blogs/blog_dto.h"

namespace Views
{
    /**
     * @brief A class representing the Update Blog view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a form that allows users to update an existing blog post.
     */
    class UpdateBlog : public View
    {
    public:
        /**
         * @brief Constructor for the UpdateBlog class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         * @param post A BlogModel object containing the current data of the blog post to be updated.
         */
        UpdateBlog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post);
    };
}

#endif