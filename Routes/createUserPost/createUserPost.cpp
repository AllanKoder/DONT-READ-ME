#include "../../Controllers/Admin/admin.h"

// /createBlog.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::createUserPost(cgi).render();
    return EXIT_SUCCESS;
}
