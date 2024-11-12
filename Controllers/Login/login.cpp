#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/login/login.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/Session/session.h"
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
    Views::View loginPost()
    {
        auto cgi = std::make_shared<cgicc::Cgicc>();

        // User is already authenticated
        if (Session::userId(cgi).has_value())
        {
            Logger::logInfo("Login Post: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi");
        }

        // Get the request body
        cgicc::CgiEnvironment env = cgi->getEnvironment();
        std::string requestBody = env.getPostData();

        Logger::logInfo("Got Request body. It is the following: " + requestBody); 
        std::unordered_map<std::string, std::string> postData = Request::getPostDataToMap(requestBody);

        // Check if the user has filled the parameters
        if (postData.count("username") == 0 || postData.count("password") == 0)
        {
            // Invalid parameters, notify
            return Views::Redirect(cgi, "/cgi-bin/login.cgi");
        }

        // Get the post data
        std::string username = postData.at("username");
        std::string password = postData.at("password");

        Logger::logInfo("Logging in with username: " + username + " password: " + password); 
        std::optional<std::string> token = Session::login(username, password);
        if (token.has_value())
        {
            // Direct to homepage with cookies
            std::string cookie = "SESSION_TOKEN=" + token.value() + "; HttpOnly";
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi" ).setCookie(cookie);
        }
        else
        {
            // Is invalid, go back to login with message
            return Views::Redirect(cgi, "/cgi-bin/login.cgi");
        }
    }

    Views::View loginPage()
    {
        auto cgi = std::make_shared<cgicc::Cgicc>();

        if (Session::userId(cgi).has_value())
        {
            Logger::logInfo("Login Page: User is already logged in");
            // Redirect to homepage
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi");
        }

        return Views::Login(cgi);
    }
}