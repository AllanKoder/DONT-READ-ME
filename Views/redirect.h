#ifndef REDIRECT_VIEW_H
#define REDIRECT_VIEW_H

#include "views.h"

namespace Views
{
    /**
     * @brief A class representing a redirect view.
     * 
     * This class inherits from the View class and is specifically
     * designed to handle redirects to other URLs.
     */
    class Redirect : public View
    {
    public:
        /**
         * @brief Constructor for the Redirect class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         * @param url The URL to which the user should be redirected.
         */
        Redirect(std::shared_ptr<cgicc::Cgicc> cgi, std::string url);
    };
}

#endif