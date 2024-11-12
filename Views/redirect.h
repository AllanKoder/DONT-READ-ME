#ifndef REDIRECT_VIEW_H
#define REDIRECT_VIEW_H
#include "views.h"

namespace Views
{
    class Redirect : public View
    {
    public:
        Redirect(std::shared_ptr<cgicc::Cgicc> cgi, std::string url);
    };
}

#endif