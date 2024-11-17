#include "blogs.view.h"
#include <sstream>
#include <vector>

namespace Views
{
    Blogs::Blogs(std::shared_ptr<cgicc::Cgicc> cgi, std::vector<Database::Requests::BlogPost> posts) : View(cgi)
    {
        setTitle("Blogs");

        std::string bodyOutput;
        // Search bar
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";
        bodyOutput += "    <input type='text' placeholder='Search...' class='border rounded-md p-2 w-full mb-4' />\n";

        // Table header
        bodyOutput += "    <table class='min-w-full bg-white border border-gray-300'>\n";
        bodyOutput += "        <thead>\n";
        bodyOutput += "            <tr class='bg-gray-200'>\n";
        bodyOutput += "                <th class='border px-4 py-2'>Name</th>\n";
        bodyOutput += "                <th class='border px-4 py-2'>Date Created</th>\n";
        bodyOutput += "                <th class='border px-4 py-2'>Title</th>\n";
        bodyOutput += "            </tr>\n";
        bodyOutput += "        </thead>\n";

        // Table body with sample data
        bodyOutput += "        <tbody>\n";
        for (const auto& post : posts) {
            bodyOutput += "            <tr>\n";
            bodyOutput += "                <td class='border px-4 py-2'>" + post.name + "</td>\n";
            bodyOutput += "                <td class='border px-4 py-2'>" + post.dateCreated + "</td>\n";
            bodyOutput += "                <td class='border px-4 py-2'>" + post.title + "</td>\n";
            bodyOutput += "            </tr>\n";
        }
        bodyOutput += "        </tbody>\n";
        bodyOutput += "    </table>\n";
        
        bodyOutput += "</div>\n";

        setBody(bodyOutput);
    }

}