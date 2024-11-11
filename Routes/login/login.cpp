#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "../../Views/sections/login/login.view.h"

int main()
{
    // Output content from the login.view.h file
    Views::Login().render();
    return EXIT_SUCCESS;
}
