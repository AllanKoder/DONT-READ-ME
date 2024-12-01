#include "../../Controllers/Blog/blog.h"

// /createBlog.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::createBlogPage(cgi).render();
    return EXIT_SUCCESS;
}
