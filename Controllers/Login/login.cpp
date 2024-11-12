#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
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
    Views::View login()
    {
        cgicc::Cgicc cgi;

        if (!Session::userId(cgi).has_value())
        {
            return Views::Seed().setBody("not valid bruv");
        }

        // Print out the submitted element
        cgicc::CgiEnvironment env = cgi.getEnvironment();
        std::string requestBody = env.getPostData();

        Logger::logInfo("Request body is the following: " + requestBody); 
        std::unordered_map<std::string, std::string> postData = Request::getPostDataToMap(requestBody);

        if (postData.count("username") == 0 || postData.count("password") == 0)
        {
            return Views::Seed().setTitle("Failed Data");
        }

        std::string username = postData.at("username");
        std::string password = postData.at("password");

        Logger::logInfo("Logging in with username: " + username + " password: " + password); 
        std::optional<std::string> token = Session::login(username, password);
        if (token.has_value())
        {
            std::string cookie = "SESSION_TOKEN=" + token.value() + "; HttpOnly";
            return Views::Seed().setBody("Foo").setCookie(cookie);
        }
        else
        {
            return Views::Seed().setBody("Poo");
        }
    }
}