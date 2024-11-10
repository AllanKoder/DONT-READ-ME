#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <cgicc/CgiEnvironment.h>
#include "cgicc/Cgicc.h"
#include <optional>

namespace Session
{   
    std::optional<int> userId();
    bool login(std::string username, std::string password);
}

#endif
