#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include "../../Controllers/Admin/admin.h"

// /createBlog.cgi
int main()
{
    // Output content from the login.view.h file
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::createUserPost(cgi).render();
    return EXIT_SUCCESS;
}
