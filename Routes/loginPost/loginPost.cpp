#include <iostream>
#include "../../Views/sections/seed/seed.view.h"
#include "../../Controllers/Login/login.h"

int main()
{
    Controllers::login().render();
    return EXIT_SUCCESS;
}
