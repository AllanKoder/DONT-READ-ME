#include "../../Controllers/Admin/admin.h"

// /createBlog.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::createUserPage(cgi).render();
    return EXIT_SUCCESS;
}
