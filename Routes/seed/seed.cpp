#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <mariadb/conncpp.hpp>

void seed()
{
}

int main()
{
    // Output HTTP headers for HTML
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;
     
    // Start HTML document
    std::cout << cgicc::html().set("lang", "en") << std::endl;
    std::cout << cgicc::head() << cgicc::title("Hello World") << cgicc::head() << std::endl;
    std::cout << cgicc::body() << std::endl;

    // Print seeded
    seed();
    std::cout << "Seeded.\n";

    // End HTML document
    std::cout << cgicc::body() << cgicc::html() << std::endl;

    return 0;
}
