#include "../../Controllers/Blog/blog.h"

// /blog.cgi/{int}
int main() {
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::blogPage(cgi).render();
    return EXIT_SUCCESS;
}