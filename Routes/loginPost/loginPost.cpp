#include <iostream>
#include "../../Controllers/Login/login.h"

int main()
{
    Controllers::loginPost().render();
    return EXIT_SUCCESS;
}
