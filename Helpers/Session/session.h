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

    struct LoginResult
    {
        bool isSessionToken;
        std::string sessionToken;
        std::string pendingSessionToken;
    };

    struct UserInfo
    {
        int id;
        PrivilegeLevel privilegeLevel;
    };

    // returns user info if logged in, otherwise null
    std::optional<UserInfo> userInfo(std::shared_ptr<cgicc::Cgicc> cgi);

    bool deleteSessionToken(int userId);

    // returns pending_session token if successful
    std::optional<LoginResult> login(std::string username, std::string password);

    // submitting the code from the email
    // returns either the auth token for the user, or go to the next stage
    // if user, get the code, if admin, go to next stage
    std::optional<LoginResult> confirmEmailCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string code);

    // for submitting the 6 digit code for admins only
    std::optional<LoginResult> confirmAuthCode(std::string pendingSessionToken);

    // create a anti-csrf token
    std::string getCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

    // check if anti-csrf token is valid
    bool isValidCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

    // check if the password follows the policy
    bool isValidPassword(std::string password);

    PrivilegeLevel stringToPrivilegeLevel(const std::string& levelStr);

    std::optional<std::string> getCookieToken(std::shared_ptr<cgicc::Cgicc> cgi, std::string cookieName);
}

#endif
