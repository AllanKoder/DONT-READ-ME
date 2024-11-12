#ifndef NAV_BAR_COMPONENT_H
#define NAV_BAR_COMPONENT_H

#include "../views.h" 
#include "cgicc/Cgicc.h"
#include <ostream>

namespace Views
{
    class NavigationBar
    {
    private:
        cgicc::Cgicc cgi;

    public:
        NavigationBar(const cgicc::Cgicc& cgi);

        // Declare the operator<< as a friend function
        friend std::ostream& operator<<(std::ostream& os, const NavigationBar& nav);
    };

    // Declare the operator<< outside the class
    std::ostream& operator<<(std::ostream& os, const NavigationBar& nav);
}

#endif