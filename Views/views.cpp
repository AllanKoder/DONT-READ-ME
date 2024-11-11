#include "views.h"
#include <iostream>
#include <cgicc/HTMLClasses.h>

namespace Views
{
    View::View()
    {
        cookies.clear();
    }

    cgicc::HTTPHTMLHeader View::getHeader()
    {
        cgicc::HTTPHTMLHeader header = cgicc::HTTPHTMLHeader();
        for (auto cookie : cookies)
        {
            header.setCookie(cookie);
        }
        return header;
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

    View& View::setCookie(cgicc::HTTPCookie cookie)
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