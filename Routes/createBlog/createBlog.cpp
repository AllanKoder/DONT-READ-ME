#include "../../Controllers/Blog/blog.h"

// /createBlog.cgi
int main()
{
    // Output content from the login.view.h file
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::createBlogPage(cgi).render();
    return EXIT_SUCCESS;
}
