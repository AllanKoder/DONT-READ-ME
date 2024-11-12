#ifndef HEADER_COMPONENT_H
#define HEADER_COMPONENT_H

#include "../views.h" 
#include "cgicc/Cgicc.h"
#include <ostream>

namespace Views
{
    class Header
    {
    private:
        std::shared_ptr<cgicc::Cgicc> cgi;

    public:
        Header(std::shared_ptr<cgicc::Cgicc> cgi);

        // Declare the operator<< as a friend function
        friend std::ostream& operator<<(std::ostream& os, const Header& nav);
    };

    // Declare the operator<< outside the class
    std::ostream& operator<<(std::ostream& os, const Header& nav);
}

#endif