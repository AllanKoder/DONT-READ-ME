#ifndef LOGIN_VIEW_H
#define LOGIN_VIEW_H
#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    class Login : public View
    {
    public:
        Login(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif