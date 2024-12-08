#ifndef APP_CODE_VIEW_H
#define APP_CODE_VIEW_H

#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    /**
     * @brief A class representing the AppCode view.
     * 
     * This class inherits from the View class and is responsible for
     * rendering a form that allows users to enter a 6-character code
     * in response to a given challenge code, simulating the hardware key.
     */
    class AppCode : public View
    {
    public:
        /**
         * @brief Constructor for the AppCode class.
         * 
         * @param cgi Shared pointer to a Cgicc object for CGI handling.
         * @param challengeCode A string representing the challenge code to be displayed in the form.
         */
        AppCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string challengeCode);
    };
}

#endif 