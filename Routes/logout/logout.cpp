#include <iostream>
#include "../../Controllers/Login/login.h"

// /logout.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::logoutPost(cgi).render();
    return EXIT_SUCCESS;
}
