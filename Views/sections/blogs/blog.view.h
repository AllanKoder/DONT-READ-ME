#ifndef BLOG_VIEW_H
#define BLOG_VIEW_H

#include <cgicc/Cgicc.h>
#include "../../views.h"
#include "../../../Helpers/Database/Blogs/blog_dto.h"

namespace Views
{
    /**
     * @brief A class representing the individual Blog post view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a page that displays a single blog post in detail,
     * with options of upvoting, and downvoting the blog, 
     * and editting if you are the creator
     */
    class Blog : public View
    {
    public:
        /**
         * @brief Constructor for the Blog class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         * @param post A BlogModel object containing the data of the blog post to be displayed.
         */
        Blog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post);
    };
}

#endif