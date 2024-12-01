#include "../../Controllers/Blog/blog.h"

// /updateBlogPost.cgi/{int}
int main() {
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::updateBlogPost(cgi).render();
    return EXIT_SUCCESS;
}