#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <cgicc/CgiEnvironment.h>
#include "cgicc/Cgicc.h"
#include <optional>

namespace Session
{   
    // returns user id if logged in, otherwise null
    std::optional<int> userId();

    // returns session token if successful
    std::optional<std::string> login(std::string username, std::string password);
}

#endif
