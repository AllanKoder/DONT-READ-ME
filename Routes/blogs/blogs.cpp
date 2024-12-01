#include "../../Controllers/Blog/blog.h"

// /blogs.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::blogsPage(cgi).render();
    return EXIT_SUCCESS;
}
