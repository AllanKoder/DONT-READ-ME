#ifndef APP_CODE_VIEW_H
#define APP_CODE_VIEW_H
#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    class AppCode : public View
    {
    public:
        AppCode(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif