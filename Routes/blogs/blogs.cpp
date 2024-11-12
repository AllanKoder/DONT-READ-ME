#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "../../Views/sections/blogs/blogs.view.h"

int main()
{
    // Output content from the login.view.h file
    Views::Blogs().render();
    return EXIT_SUCCESS;
}
