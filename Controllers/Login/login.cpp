#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/login/login.view.h"
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
        if (Session::userId(cgi).has_value())
        {
            Logger::logInfo("Login Post: User is already logged in");
            // Redirect to homepage with notification
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in!");
        }

        // Get the request body
        cgicc::CgiEnvironment env = cgi->getEnvironment();
        std::string requestBody = env.getPostData();

        Logger::logInfo("Got Request body. It is the following: " + requestBody); 
        std::unordered_map<std::string, std::string> postData = Request::getPostDataToMap(requestBody);

        // Check if the user has filled the parameters
        if (postData.count("email") == 0 || postData.count("password") == 0)
        {
            // Invalid parameters, notify and redirect back to login
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Please fill out all fields.");
        }

        // Get the post data
        std::string email = StringHelpers::urlDecode(postData.at("email"));
        std::string password = StringHelpers::urlDecode(postData.at("password"));

        Logger::logInfo("Logging in with email: " + email + " password: " + password); 
        std::optional<std::string> token = Session::login(email, password);
        
        if (token.has_value())
        {
            // Direct to homepage with cookies and success notification
            std::string cookie = "SESSION_TOKEN=" + token.value() + "; HttpOnly";
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

    Views::View loginPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        if (Session::userId(cgi).has_value())
        {
            Logger::logInfo("Login Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Already Logged in");
        }

        return Views::Login(cgi);
    }
}