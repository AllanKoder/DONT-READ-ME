#ifndef BLOGS_VIEW_H
#define BLOGS_VIEW_H

#include <cgicc/Cgicc.h>
#include "../../views.h"
#include "../../../Helpers/Database/Blogs/blog_dto.h"

namespace Views
{
    /**
     * @brief A class representing the Blogs view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a page that displays a list of blog posts.
     */
    class Blogs : public View
    {
    public:
        /**
         * @brief Constructor for the Blogs class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         * @param posts A vector containing BlogModel objects, each representing a blog post to be displayed.
         */
        Blogs(std::shared_ptr<cgicc::Cgicc> cgi, std::vector<Database::Requests::BlogModel> posts);
    };
}

#endif