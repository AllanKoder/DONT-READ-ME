#ifndef EMAIL_CODE_VIEW_H
#define EMAIL_CODE_VIEW_H
#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    class Email : public View
    {
    public:
        Email(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif