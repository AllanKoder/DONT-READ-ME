#include "create_user.view.h"
#include "../../../Helpers/Session/session.h"
#include "../../../Helpers/String/string_helpers.h"
#include "../../components/csrf_token.comp.h"
#include <sstream>
#include <vector>

namespace Views
{
    CreateUser::CreateUser(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        setTitle("Create User");
        std::string bodyOutput;

        // Main container for the form
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";

        // Form for updating a blog
        bodyOutput += "    <form action='/cgi-bin/createUserPost.cgi/' method='POST' class='space-y-4'>\n";
        bodyOutput += "        <label for='username' class='block text-sm font-medium text-gray-700'>Username</label>\n";
        bodyOutput += "        <input type='text' name='username' id='username' class='border rounded-md p-2 w-full' required />\n";

        bodyOutput += "        <label for='email' class='block text-sm font-medium text-gray-700'>Email</label>\n";
        bodyOutput += "        <input type='text' name='email' id='email' class='border rounded-md p-2 w-full' required />\n";

        bodyOutput += "        <label for='password' class='block text-sm font-medium text-gray-700'>Password:</label>\n";
        bodyOutput += "        <input type='password' name='password' id='password' class='border rounded-md p-2 w-full' required />\n";

        // CSRF Token
        bodyOutput += CsrfToken(cgi).Render();

        bodyOutput += "        <button type='submit' class='bg-blue-500 text-white rounded-md p-2'>Update</button>\n";
        bodyOutput += "    </form>\n";

        bodyOutput += "</div>\n"; // End of main container

        setBody(bodyOutput);
    }
}