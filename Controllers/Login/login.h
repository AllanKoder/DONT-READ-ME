#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "../../Views/views.h"

namespace Controllers
{
    /**
     * @brief Handles the POST request for user login.
     * 
     * This function processes the login data submitted by the user and returns a View 
     * representing the result of the login attempt (e.g., success or failure).
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the login request.
     */
    Views::View loginPost(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the POST request for user logout.
     * 
     * This function processes the logout request and returns a View representing
     * the result of the logout operation.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the logout request.
     */
    Views::View logoutPost(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays the login page.
     * 
     * This function returns a View that renders the login page where users can enter
     * their credentials.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the login page.
     */
    Views::View loginPage(std::shared_ptr<cgicc::Cgicc> cgi);

    // Multi-Factor Authentication (MFA) Functions

    /**
     * @brief Displays the email code verification page.
     * 
     * This function returns a View that renders the page where users can enter
     * their email verification code for MFA2.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the email code verification page.
     */
    Views::View emailCodePage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the POST request for email code verification.
     * 
     * This function processes the email verification code submitted by the user and
     * returns a View representing the result of the verification attempt.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the email code verification request.
     */
    Views::View emailCodePost(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays the app code verification page.
     *
     * This function returns a View that renders the page where users can enter
     * their app verification code for the hardware key MFA2.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the app code verification page.
     */
    Views::View appCodePage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the POST request for app code verification.
     *
     * This function processes the app verification code submitted by the user and
     * returns a View representing the result of the verification attempt.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the app code verification request.
     */
    Views::View appCodePost(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif 