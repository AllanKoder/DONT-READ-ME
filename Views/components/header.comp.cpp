#include "header.comp.h"
#include <sstream>
#include "../../Helpers/Session/session.h"

namespace Views
{
    Header::Header(std::shared_ptr<cgicc::Cgicc> _cgi) : cgi(_cgi) {};

    std::string Header::Render() const
    {
        std::string output_text;
        output_text += "<header class=\"bg-gray-100 shadow-md border-b border-gray-300\">\n";
        output_text += "    <div class=\"max-w-7xl mx-auto py-4 px-4 sm:px-6 lg:px-8 flex items-center justify-between\">\n";

        std::optional<Session::UserInfo> userInfo = Session::userInfo(this->cgi);
        bool isLoggedIn = userInfo.has_value();
        if (isLoggedIn)
        {
            // User is authenticated, display as hyperlink
            output_text += "        <h1 class=\"text-3xl font-bold text-gray-900\">\n";
            output_text += "            <a href=\"/cgi-bin/blogs.cgi\" class=\"text-blue-600 hover:text-blue-800\">don't README</a>\n";
            output_text += "        </h1>\n";
        }
        else
        {
            // User is not authenticated, display as regular text
            output_text += "        <h1 class=\"text-3xl font-bold text-gray-900\">don't README</h1>\n";
        }
        // Check if the user is the admin
        if (userInfo.has_value() && userInfo.value().privilegeLevel == Session::ADMIN)
        {
            // Create a user
            output_text += "        <div>\n";
            output_text += "            <a href=\"/cgi-bin/createUser.cgi\" class=\"text-blue-600 hover:text-blue-800\">Create User</a>\n";
            output_text += "        </div>\n";
        }

        // Check if the user is logged in
        if (isLoggedIn)

        {
            // Create a blog
            output_text += "        <div>\n";
            output_text += "            <a href=\"/cgi-bin/createBlog.cgi\" class=\"text-blue-600 hover:text-blue-800\">Create Blog</a>\n";
            output_text += "        </div>\n";
            
            // Show their username
            output_text += "        <div>\n";
            output_text += "            <p>Hello, " + userInfo.value().username + "</p>\n";
            output_text += "        </div>\n";
            
            // Print the Logout header
            output_text += "        <div>\n";
            output_text += "            <a href=\"/cgi-bin/logout.cgi\" class=\"text-blue-600 hover:text-blue-800\">Logout</a>\n";
            output_text += "        </div>\n";
        }

        output_text += "    </div>\n";
        output_text += "</header>\n";

        return output_text;
    }
}