#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/Session/session.h"
#include <iostream>
#include <cgicc/HTTPCookie.h>

namespace Controllers
{
    Views::View login()
    {
        if (Session::login("user", "password"))
        {
            return Views::Seed().setTitle("Foo").setCookie(cgicc::HTTPCookie("count","1"));
        }
        else
        {
            return Views::Seed().setTitle("Poo");
        }
    }
}