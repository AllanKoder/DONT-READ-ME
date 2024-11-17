#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include "../../Controllers/Blog/blog.h"

int main()
{
    // Output content from the login.view.h file
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::blogsPage(cgi).render();
    return EXIT_SUCCESS;
}
