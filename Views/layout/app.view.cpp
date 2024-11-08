#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

namespace Views
{
    void AppLayoutStart()
    {
        // Output HTTP headers for HTML
        std::cout << cgicc::HTTPHTMLHeader() << std::endl;
        
        // Start HTML document
        std::cout << cgicc::html().set("lang", "en") << std::endl;
        std::cout << cgicc::head() << cgicc::title("Hello World") << cgicc::head() << std::endl;
        std::cout << cgicc::body() << std::endl;
    }

    void AppLayoutEnd()
    {
        // End HTML document
        std::cout << cgicc::body() << cgicc::html() << std::endl;
    }
}