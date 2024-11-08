#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "../../Views/sections/login/login.view.h"

int main()
{
    // Output HTTP headers for HTML
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;
    
    // Start HTML document
    std::cout << cgicc::html().set("lang", "en") << std::endl;
    std::cout << cgicc::head() << cgicc::title("Hello World") << cgicc::head() << std::endl;
    std::cout << cgicc::body() << std::endl;

    // Output content from the login.view.h file
    Views::login();

    // End HTML document
    std::cout << cgicc::body() << cgicc::html() << std::endl;

    return 0;
}
