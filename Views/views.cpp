#include "views.h"
#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

namespace Views
{
    void View::render()
    {
        // Output HTTP headers
        std::cout << cgicc::HTTPHTMLHeader() << std::endl;
        std::cout << headers;
        
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
        headers += "Set-Cookie: " + cookie + "\r\n";
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