#include <iostream>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

namespace Views
{
    void login()
    {
        std::cout << cgicc::h1("Login Page") << "\n";
        std::cout << "<form action='/cgi-bin/Routes/login.cgi' method='POST'>" << "\n";
        std::cout << "Username: <input type='text' name='username'><br>" << "\n";
        std::cout << "Password: <input type='password' name='password'><br>" << "\n";
        std::cout << "<input type='submit' value='Login'>" << "\n";
        std::cout << "</form>" << "\n";    
    }
}