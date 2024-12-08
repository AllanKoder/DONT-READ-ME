#ifndef LOGIN_VIEW_H
#define LOGIN_VIEW_H
#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    /**
     * @brief A class representing the Login view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a login form that allows users to enter their email
     * and password for authentication.
     */
    class Login : public View
    {
    public:
        /**
         * @brief Constructor for the Login class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        Login(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif