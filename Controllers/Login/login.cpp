#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/Session/session.h"
#include <iostream>

namespace Controllers
{
    Views::View login()
    {
        if (Session::login("user", "password"))
        {
            return Views::Seed().setTitle("Foo");
        }
        else
        {
            return Views::Seed().setTitle("Poo");
        }
    }
}