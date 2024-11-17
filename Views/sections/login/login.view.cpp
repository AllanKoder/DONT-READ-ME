#include "login.view.h"
#include <string>

namespace Views
{
    Login::Login(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        std::string bodyOutput = "";
        bodyOutput += "<div class='bg-white p-8 rounded-lg'>\n";
        bodyOutput += "   <h2 class='text-2xl font-bold mb-6 text-center'>Login</h2>\n";
        bodyOutput += "        <form action='/cgi-bin/loginPost.cgi' method='POST'>\n";
        bodyOutput += "            <label for='username' class='block text-sm font-medium text-gray-700'>Username:</label>\n";
        bodyOutput += "            <input type='text' id='username' name='username' class='mt-1 block w-full border border-gray-300 rounded-md p-2' required><br>\n";
        bodyOutput += "            <label for='password' class='block text-sm font-medium text-gray-700 mt-4'>Password:</label>\n";
        bodyOutput += "            <input type='password' id='password' name='password' class='mt-1 block w-full border border-gray-300 rounded-md p-2' required><br>\n";
        bodyOutput += "       <input type='submit' value='Login' class='mt-6 w-full bg-blue-500 text-white font-bold py-2 rounded hover:bg-blue-600'>\n";
        bodyOutput += "   </form>\n";
        bodyOutput += "</div>\n";

        setBody(bodyOutput);
        setTitle("Login");
    }
}