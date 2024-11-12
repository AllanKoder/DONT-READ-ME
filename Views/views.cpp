#include "views.h"
#include <iostream>
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPRedirectHeader.h>
#include "../Logger/logger.h"
#include <sstream>   

namespace Views
{
    View::View() : redirectUrl(""), body(""), headers("")
    {
        title = "No Title";
        cookies.clear();

        // Libraries
        scripts = "<script src=\"https://cdn.tailwindcss.com\"></script>\n";
    }

    View::View(const cgicc::Cgicc& cgi) : redirectUrl(""), body(""), headers("")
    {
        title = "No Title";
        cookies.clear();

        // Libraries
        scripts = "<script src=\"https://cdn.tailwindcss.com\"></script>\n";
    }

    std::string View::getHeader()
    {
        std::ostringstream outputHeader;

        if (!redirectUrl.empty())
        {
            // There is a redirect, set it as the header
            outputHeader << "Status: 301 Moved Permanently\n";
            outputHeader << "Location: " << redirectUrl << "\n";
        }
        else
        {
            // If there's no redirect, proceed with the normal header
            outputHeader << "Content-Type: text/html\n";
        }

        // Add custom headers
        outputHeader << headers;

        // Add cookies
        for (const auto& cookie : cookies)
        {
            outputHeader << "Set-Cookie: " << cookie << "\n";
        }

        outputHeader << "\n";
        return outputHeader.str();
    }

    void View::render()
    {
        // Output HTTP headers
        std::cout << getHeader() << std::endl;
        
        // Start HTML document
        std::cout << cgicc::html().set("lang", "en") << std::endl;
       
        // Start the <head>
        std::cout << cgicc::head() << std::endl;
        std::cout << cgicc::title(title) << std::endl;
        std::cout << scripts << std::endl;
        std::cout << cgicc::head() <<std::endl;
        // End </head>
        
        // Start the body
        std::cout << cgicc::body() << std::endl;
        // Print body
        std::cout << body << std::endl;
        
        // End HTML document
        std::cout << cgicc::body() << cgicc::html() << std::endl;

    }

    View& View::setRedirect(const std::string& url) {
        redirectUrl = url;
        return *this;
    }
    
    View& View::setHeader(std::string header)
    {
        headers += header + "\r\n";
        return *this;
    }

    View& View::setCookie(std::string cookie)
    {
        cookies.push_back(cookie);
        return *this;
    }

    View& View::setBody(std::string newBody)
    {
        body = newBody;
        return *this;
    }

    View& View::setTitle(std::string newTitle)
    {
        title = newTitle;
        return *this;
    }
    
    View& View::setNotification(NotificationType type, std::string message)
    {

        return *this;
    }
}