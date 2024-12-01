#include "../../Controllers/Blog/blog.h"

// /updateBlog.cgi/{int}
int main() {
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::updateBlogPage(cgi).render();
    return EXIT_SUCCESS;
}