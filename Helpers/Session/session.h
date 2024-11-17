#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <cgicc/CgiEnvironment.h>
#include "cgicc/Cgicc.h"
#include <optional>
#include <memory>

namespace Session
{
    enum PrivilegeLevel
    {
        ADMIN,
        USER
    };

    struct UserInfo
    {
        int id;
        PrivilegeLevel privelegeLevel;
    };

    // returns user info if logged in, otherwise null
    std::optional<UserInfo> userInfo(std::shared_ptr<cgicc::Cgicc> cgi);

    bool deleteSessionToken(int userId);

    // returns session token if successful
    std::optional<std::string> login(std::string username, std::string password);

    // create a anti-csrf token
    std::string getCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

    // check if anti-csrf token is valid
    bool isValidCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi, std::string token);

    PrivilegeLevel stringToPrivilegeLevel(const std::string& levelStr);

    std::optional<std::string> getSessionToken(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif
