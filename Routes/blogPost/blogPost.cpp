#include "../../Controllers/Blog/blog.h"

// /blogPost.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::postBlogPage(cgi).render();
    return EXIT_SUCCESS;
}
