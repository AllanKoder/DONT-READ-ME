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
    }

    std::string View::getHeader()
    {
        // If there's no redirect, proceed with the normal header
        std::string outputHeader = "Content-Type: text/html\n";
        if (!redirectUrl.empty())
        {
            // There is a redirect, set it as the header
            cgicc::HTTPRedirectHeader redirectHeader(redirectUrl, 307);
            std::ostringstream oss;
            oss << redirectHeader;
            
            outputHeader = oss.str();
        }
        
        outputHeader += headers;

        for (const auto& cookie : cookies)
        {
            outputHeader += "Set-Cookie: " + cookie + "\n";
        }
        
        outputHeader += "\n\n";
        return outputHeader;
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
        std::cout << cgicc::head() <<std::endl;
        // End </head>
        
        // Start the body
        std::cout << cgicc::body() << std::endl;
        // Print body
        std::cout << body;
        
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
}