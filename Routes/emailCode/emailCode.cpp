#include <iostream>
#include "../../Controllers/Login/login.h"

// /login.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    // Output content from the login.view.h file
    Controllers::emailCodePage(cgi).render();
    return EXIT_SUCCESS;
}