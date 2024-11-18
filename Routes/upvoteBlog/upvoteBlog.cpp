#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>
#include "../../Controllers/Blog/blog.h"

int main() {
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::upvoteBlog(cgi).render();
    return EXIT_SUCCESS;
}