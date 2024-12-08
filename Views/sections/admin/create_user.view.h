#ifndef BLOG_VIEW_H
#define BLOG_VIEW_H

#include "../../views.h"
#include <vector>
#include <cgicc/Cgicc.h>

namespace Views
{
    /**
     * @brief A class representing the Create User view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a form that allows the creation of a new user account.
     */
    class CreateUser : public View
    {
    public:
        /**
         * @brief Constructor for the CreateUser class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        CreateUser(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif