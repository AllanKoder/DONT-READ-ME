#include "login.h"
#include <mariadb/conncpp.hpp>
#include <string.h>
#include "../../Logger/logger.h"
#include "../../Views/sections/seed/seed.view.h"
#include "../../Helpers/Database/Users/users.h"
#include "../../Helpers/Session/session.h"
#include <iostream>
#include <cgicc/HTTPCookie.h>
#include <optional>
#include <string>

namespace Controllers
{
    Views::View login()
    {
        std::optional<std::string> token = Session::login("user", "password");
        if (token.has_value())
        {
            std::string cookie = "SESSION_TOKEN=" + token.value() + "; HttpOnly";
            return Views::Seed().setTitle("Foo").setCookie(cookie);
        }
        else
        {
            return Views::Seed().setTitle("Poo");
        }
    }
}