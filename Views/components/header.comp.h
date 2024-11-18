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
        std::string Render() const;
    };

}

#endif