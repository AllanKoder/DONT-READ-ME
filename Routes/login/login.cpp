#include <iostream>
#include "../../Controllers/Login/login.h"

int main()
{
    // Output content from the login.view.h file
    Controllers::loginPage().render();
    return EXIT_SUCCESS;
}
