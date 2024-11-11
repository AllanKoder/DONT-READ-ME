#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include "../../Views/sections/seed/seed.view.h"
#include "../../Controllers/Login/login.h"

int main()
{
    cgicc::Cgicc cgi;
    // Print out the submitted element
    // cgicc::CgiEnvironment env = cgi.getEnvironment();

    // std::string requestMethod = env.getPostData();
    // std::cout << requestMethod << "\n";


    // Close the HTML document
    Controllers::login().render();
    return EXIT_SUCCESS;
}
