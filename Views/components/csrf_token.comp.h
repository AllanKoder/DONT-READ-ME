#ifndef CSRF_TOKEN_COMPONENT_H
#define CSRF_TOKEN_COMPONENT_H

#include "../views.h" 
#include "cgicc/Cgicc.h"
#include <ostream>

namespace Views
{
    /**
     * @brief A class representing the CSRF Token component.
     * 
     * This class is responsible for generating a CSRF (Cross-Site Request Forgery) 
     * token input field to be included in forms for security purposes.
     */
    class CsrfToken
    {
    private:
        // Shared pointer to Cgicc object for CGI handling.
        std::shared_ptr<cgicc::Cgicc> cgi;  

    public:
        /**
         * @brief Constructor for the CsrfToken class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        CsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

        /**
         * @brief Renders the CSRF token as a hidden input field.
         * 
         * @return std::string The HTML string containing the hidden input field with the CSRF token.
         */
        std::string Render() const;
    };
}

#endif