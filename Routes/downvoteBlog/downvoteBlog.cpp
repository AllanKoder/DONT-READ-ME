#include "../../Controllers/Blog/blog.h"

// /downvoteBlog.cgi/{int}
int main() {
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::downvoteBlog(cgi).render();
    return EXIT_SUCCESS;
}