#include "views.h"
#include <iostream>
#include <cgicc/HTMLClasses.h>
#include "../Logger/logger.h"
#include <sstream>   

namespace Views
{
    View::View()
    {
        cookies.clear();
    }

    std::string View::getHeader()
    {
        std::string outputHeader = "Content-Type: text/html\n";
        for (auto cookie : cookies)
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
        std::cout << cgicc::head() << cgicc::title(title) << cgicc::head() << std::endl;
        std::cout << cgicc::body() << std::endl;
        
        // Print body
        std::cout << body;
        
        // End HTML document
        std::cout << cgicc::body() << cgicc::html() << std::endl;

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