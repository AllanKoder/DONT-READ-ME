#include "../../Controllers/Login/login.h"

// /loginPost.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::loginPost(cgi).render();
    return EXIT_SUCCESS;
}
