#include "login.view.h"
#include <string>

namespace Views
{
    Login::Login(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        std::string bodyOutput = "";
        bodyOutput += "<form action='/cgi-bin/loginPost.cgi' method='POST'>\n";
        bodyOutput += "Username: <input type='text' name='username'><br>\n";
        bodyOutput += "Password: <input type='password' name='password'><br>\n";
        bodyOutput += "<input type='submit' value='Login'>\n";
        bodyOutput += "</form>\n";
        
        setBody(bodyOutput);
        setTitle("Login");
    }
}