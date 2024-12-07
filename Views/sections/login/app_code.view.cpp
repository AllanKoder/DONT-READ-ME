#include "app_code.view.h"
#include <string>

namespace Views
{
    AppCode::AppCode(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        std::string bodyOutput = "";

        bodyOutput += "<form action='/cgi-bin/appCodePost.cgi' method='POST'>\n";
        bodyOutput += "    <div class='mb-4'>\n";
        bodyOutput += "        <label for='code' class='block text-sm font-medium text-gray-700 mb-2'>6 character code (App):</label>\n";
        bodyOutput += "        <input type='text' id='code' name='code' \n";
        bodyOutput += "            class='w-full px-3 py-2 text-center text-xl border border-gray-300 rounded-md focus:outline-none focus:ring-2 focus:ring-blue-500' \n";
        bodyOutput += "            required \n";
        bodyOutput += "            pattern='[a-zA-Z0-9]{6}' \n";
        bodyOutput += "            maxlength='6' \n";
        bodyOutput += "            title='Please enter a 6 character code'>\n";
        bodyOutput += "    </div>\n";
        bodyOutput += "    <button type='submit' \n";
        bodyOutput += "        class='w-full bg-blue-500 text-white font-bold py-2 px-4 rounded hover:bg-blue-600 focus:outline-none focus:ring-2 focus:ring-blue-400 focus:ring-opacity-50'>\n";
        bodyOutput += "        Submit\n";
        bodyOutput += "    </button>\n";
        bodyOutput += "</form>\n";

        setBody(bodyOutput);
        setTitle("Enter 2-Char Code");
    }
}