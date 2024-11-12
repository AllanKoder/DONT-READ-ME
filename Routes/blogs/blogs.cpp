#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include "../../Views/sections/blogs/blogs.view.h"

int main()
{
    // Output content from the login.view.h file
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Views::Blogs(cgi).render();
    return EXIT_SUCCESS;
}
