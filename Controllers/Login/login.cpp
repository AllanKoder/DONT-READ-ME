#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/login/login.view.h"
#include "../../Views/sections/login/email.view.h"
#include "../../Views/sections/login/app_code.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/Session/session.h"
#include "../../Helpers/String/string_helpers.h"
#include "../../Helpers/Request/request.h"
#include <iostream>
#include <cgicc/HTTPCookie.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include <unordered_map>
#include <optional>
#include <string>

namespace Controllers
{
    Views::View loginPost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        // User is already authenticated
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("Login Post: User is already logged in");
            // Redirect to homepage with notification
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in!");
        }

        // Get the post data
        std::string email = cgi->getElement("email")->getValue();
        std::string password = cgi->getElement("password")->getValue();

        if (email.empty() || password.empty())
        {
            // Invalid parameters, notify and redirect back to login
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Please fill out all fields.");
        }

        Logger::logInfo("Logging in with email: " + email + " password: " + password);

        std::optional<Session::LoginResult> loginResult = Session::login(email, password);

        if (loginResult.has_value())
        {
            // Direct to homepage with cookies and success notification
            std::string cookie = "PENDING_SESSION_TOKEN=" + loginResult.value().pendingSessionToken + "; HttpOnly ; SameSite=Strict";
            return Views::Redirect(cgi, "/cgi-bin/emailCode.cgi")
                .setCookie(cookie)
                .setNotification(Views::NotificationType::SUCCESS, "Check your email for the auth code!");
        }
        else
        {
            // Invalid credentials, go back to login with error notification
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Invalid email or password.");
        }
    }

    Views::View logoutPost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (!userInfo.has_value())
        {
            Logger::logInfo("User is trying to log out while logged in.");
            // Redirect to login
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Not Logged in");
        }

        // Delete all session tokens of user Id
        Session::deleteSessionToken(userInfo.value().id);

        // Set as null cookie
        std::string cookie = "SESSION_TOKEN=; Max-Age=0; HttpOnly";
        return Views::Redirect(cgi, "/cgi-bin/login.cgi")
            .setCookie(cookie)
            .setNotification(Views::NotificationType::SUCCESS, "Successfully logged out!");
    }

    Views::View loginPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("Login Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        return Views::Login(cgi);
    }

    Views::View emailCodePage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("email Code Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        if (!Session::getCookieToken(cgi, "PENDING_SESSION_TOKEN").has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "No need to go there.");
        }

        return Views::Email(cgi);
    }

    Views::View emailCodePost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("email Code Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        // Check if their code is valid.
        // Don't need to worry about CSRF since this is logging in.
        std::string code = cgi->getElement("code")->getValue();
        if (code.empty())
        {
            return Views::Redirect(cgi, "/cgi-bin/emailCode.cgi")
                .setNotification(Views::NotificationType::WARNING, "No Code given");
        }

        std::optional<Session::LoginResult> loginResult = Session::confirmEmailCode(cgi, code);
        if (!loginResult.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/emailCode.cgi")
                .setNotification(Views::NotificationType::WARNING, "Email code was not correct");
        }
        else
        {
            // This is the session token, the user can log in
            if (loginResult.value().isSessionToken)
            {
                // Set the session token
                std::string sessionCookie = "SESSION_TOKEN=" + loginResult.value().sessionToken + "; HttpOnly ; SameSite=Strict";
                // Delete the temp session cookie
                std::string pendingSessionCookie = "PENDING_SESSION_TOKEN=; Max-Age=0; HttpOnly";
                return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                    .setCookie(sessionCookie)
                    .setCookie(pendingSessionCookie)
                    .setNotification(Views::NotificationType::SUCCESS, "Login Success! Welcome Back!");
            }
            // this is the admin, they need the next step
            else
            {
                // Set the next pending Session Token
                std::string pendingSessionCookie = "PENDING_SESSION_TOKEN=" + loginResult.value().pendingSessionToken + "; HttpOnly";
                return Views::Redirect(cgi, "/cgi-bin/appCode.cgi")
                    .setCookie(pendingSessionCookie)
                    .setNotification(Views::NotificationType::SUCCESS, "Enter the code from the MFA2 App");
            }
        }
    }

    Views::View appCodePage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("email Code Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        if (!Session::getCookieToken(cgi, "PENDING_SESSION_TOKEN").has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "No need to go there.");
        }

        return Views::AppCode(cgi);
    }

    Views::View appCodePost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userInfo(cgi).has_value())
        {
            Logger::logInfo("email Code Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        // Check if their code is valid.
        // Don't need to worry about CSRF since this is logging in.
        std::string code = cgi->getElement("code")->getValue();
        if (code.empty())
        {
            return Views::Redirect(cgi, "/cgi-bin/appCode.cgi")
                .setNotification(Views::NotificationType::WARNING, "No Code given");
        }

        std::optional<Session::LoginResult> loginResult = Session::confirmAuthCode(cgi, code);
        if (!loginResult.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/appCode.cgi")
                .setNotification(Views::NotificationType::WARNING, "Email code was not correct");
        }

        // Set the session token
        std::string sessionCookie = "SESSION_TOKEN=" + loginResult.value().sessionToken + "; HttpOnly ; SameSite=Strict";
        // Delete the temp session cookie
        std::string pendingSessionCookie = "PENDING_SESSION_TOKEN=; Max-Age=0; HttpOnly";
        return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
            .setCookie(sessionCookie)
            .setCookie(pendingSessionCookie)
            .setNotification(Views::NotificationType::SUCCESS, "Login Success! Welcome Back!");
    }
}
