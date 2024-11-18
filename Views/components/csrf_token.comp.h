#ifndef CSRF_TOKEN_COMPONENT_H
#define CSRF_TOKEN_COMPONENT_H

#include "../views.h" 
#include "cgicc/Cgicc.h"
#include <ostream>

namespace Views
{
    class CsrfToken
    {
    private:
        std::shared_ptr<cgicc::Cgicc> cgi;

    public:
        CsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);
        std::string Render() const;
    };
}

#endif