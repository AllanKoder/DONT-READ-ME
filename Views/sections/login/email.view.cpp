#include "email.view.h"
#include <string>

namespace Views
{
    Email::Email(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        std::string bodyOutput = "";

        bodyOutput += "<form action='/cgi-bin/emailCodePost.cgi' method='POST'>\n";
        bodyOutput += "    <div class='mb-4'>\n";
        bodyOutput += "        <label for='code' class='block text-sm font-medium text-gray-700 mb-2'>6-Digit Code:</label>\n";
        bodyOutput += "        <div class='flex justify-center space-x-2'>\n"; // Added space between inputs
        for (int i = 1; i <= 6; i++) {
            bodyOutput += "            <input type='text' id='code" + std::to_string(i) + "' name='code" + std::to_string(i) + "' \n";
            bodyOutput += "                class='w-12 h-12 text-center text-xl border border-gray-300 rounded-md focus:outline-none focus:ring-2 focus:ring-blue-500' \n";
            bodyOutput += "                required \n";
            bodyOutput += "                pattern='[a-zA-Z0-9]' \n";
            bodyOutput += "                maxlength='1' \n";
            bodyOutput += "                oninput='if(this.value.length === 1) { this.nextElementSibling ? this.nextElementSibling.focus() : this.form.querySelector(\"button\").focus(); }' \n";
            bodyOutput += "                onkeydown='if(event.key === \"Backspace\" && this.value.length === 0) { this.previousElementSibling && this.previousElementSibling.focus(); }' \n";
            bodyOutput += "                title='Please enter a single letter or number'>\n";
        }
        bodyOutput += "        </div>\n"; // Closing flex container
        bodyOutput += "    </div>\n"; // Closing mb-4
        bodyOutput += "    <button type='submit' \n";
        bodyOutput += "        class='w-full bg-blue-500 text-white font-bold py-2 px-4 rounded hover:bg-blue-600 focus:outline-none focus:ring-2 focus:ring-blue-400 focus:ring-opacity-50'>\n";
        bodyOutput += "        Submit\n";
        bodyOutput += "    </button>\n";
        bodyOutput += "</form>\n";

        setBody(bodyOutput);
        setTitle("Enter 6-Digit Code");
    }
}