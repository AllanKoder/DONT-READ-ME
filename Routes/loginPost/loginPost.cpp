#include <iostream>
#include "../../Controllers/Login/login.h"

int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::loginPost(cgi).render();
    return EXIT_SUCCESS;
}
