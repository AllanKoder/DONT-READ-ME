#ifndef SEED_VIEW_H
#define SEED_VIEW_H

#include "../../views.h"
#include <cgicc/Cgicc.h>

namespace Views
{
    class Seed : public View 
    {
    public:
        Seed(std::shared_ptr<cgicc::Cgicc> cgi);
    };
}

#endif