#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <cgicc/CgiEnvironment.h>

namespace Session
{
    bool isValidUsernamePassword(std::string username, std::string password);
    std::string getTokenOrCreate(std::string username, std::string password);
    bool isValidToken(cgicc::CgiEnvironment environment);
}

#endif
