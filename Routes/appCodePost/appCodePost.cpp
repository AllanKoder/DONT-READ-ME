#include "../../Controllers/Login/login.h"

// /login.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::appCodePost(cgi).render();
    return EXIT_SUCCESS;
}
