#ifndef HEADER_COMPONENT_H
#define HEADER_COMPONENT_H

#include "../views.h" 
#include "cgicc/Cgicc.h"
#include <ostream>

namespace Views
{
    /**
     * @brief A class representing the Header component.
     * 
     * This class is responsible for generating the header section of the webpage,
     * which includes the site title, navigation links, and user-specific information.
     */
    class Header
    {
    private:
        // Shared pointer to Cgicc object for CGI handling.
        std::shared_ptr<cgicc::Cgicc> cgi;  

    public:
        /**
         * @brief Constructor for the Header class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        Header(std::shared_ptr<cgicc::Cgicc> cgi);

        /**
         * @brief Renders the header component.
         * 
         * This method generates the HTML for the header, including:
         * - Site title (as a link for authenticated users)
         * - "Create User" link for admin users
         * - "Create Blog" link for authenticated users
         * - User greeting and logout link for authenticated users
         * 
         * @return std::string The HTML string containing the rendered header.
         */
        std::string Render() const;
    };
}

#endif