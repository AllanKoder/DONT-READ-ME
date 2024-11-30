#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/login/login.view.h"
#include "../../Views/sections/login/email.view.h"
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
        std::optional<std::string> token = Session::login(email, password);
        
        if (token.has_value())
        {
            // Direct to homepage with cookies and success notification
            std::string cookie = "SESSION_TOKEN=" + token.value() + "; HttpOnly ; SameSite=Strict";
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setCookie(cookie)
                .setNotification(Views::NotificationType::SUCCESS, "Login successful! Welcome back.");
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
        std::string cookie = "SESSION_TOKEN=; HttpOnly";
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

        return Views::Email(cgi);
    }
}