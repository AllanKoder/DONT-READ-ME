#ifndef BLOG_CONTROLLER_H
#define BLOG_CONTROLLER_H

#include <memory>
#include "../../Views/views.h"

namespace Controllers
{
    /**
     * @brief Displays the page for creating a new user.
     * 
     * A View that renders the form where administrators
     * can enter details to create a new user account.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the create user page.
     */
    Views::View createUserPage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the POST request for creating a new user.
     * 
     * Processes the submitted data from the create user form and attempts
     * to create a new user in the system, returning an appropriate view based on the
     * success or failure of the operation.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the create user request.
     */
    Views::View createUserPost(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif // BLOG_CONTROLLER_H