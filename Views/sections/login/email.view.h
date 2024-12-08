#ifndef EMAIL_CODE_VIEW_H
#define EMAIL_CODE_VIEW_H

#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    /**
     * @brief A class representing the Email code entry view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a form that allows users to enter a 6-character code
     * that was emailed to them.
     */
    class Email : public View
    {
    public:
        /**
         * @brief Constructor for the Email class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         */
        Email(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif