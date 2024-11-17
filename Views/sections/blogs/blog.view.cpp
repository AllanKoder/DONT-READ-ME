#include "blog.view.h"
#include <sstream>
#include <vector>

namespace Views
{
    Blog::Blog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post) : View(cgi)
    {
        setTitle("Blogs");

        std::string bodyOutput;
        // Search bar
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";
        
        bodyOutput += "    <form hx-get='/cgi-bin/blogs.cgi' hx-select='#table-container' \
        hx-target='#table-container' hx-swap='innerHTML' hx-trigger='keyup changed delay:500ms'>\n"; // Form to submit search
        bodyOutput += "        <input type='text' name='search' placeholder='Search...' class='border rounded-md p-2 w-full mb-4' />\n";
        bodyOutput += "        <button type='submit' class='hidden'></button>\n";
        bodyOutput += "    </form>\n";


        // Scrollable table container
        bodyOutput += "    <div id='table-container' class='overflow-y-auto' style='max-height: 400px;'>\n"; // Adjust max-height as needed
        bodyOutput += "        <table class='min-w-full bg-white border border-gray-300'>\n";
        bodyOutput += "            <thead>\n";
        bodyOutput += "                <tr class='bg-gray-200'>\n";
        bodyOutput += "                    <th class='border px-4 py-2'>Upvotes</th>\n";
        bodyOutput += "                    <th class='border px-4 py-2'>Name</th>\n";
        bodyOutput += "                    <th class='border px-4 py-2'>Title</th>\n";
        bodyOutput += "                </tr>\n";
        bodyOutput += "            </thead>\n";

        // Table body with sample data
        bodyOutput += "            <tbody>\n";
        bodyOutput += "                <tr>\n";
        bodyOutput += "                    <td class='border px-4 py-2'>" + std::to_string(post.upvotes) + "</td>\n";
        bodyOutput += "                    <td class='border px-4 py-2'>" + post.username + "</td>\n";
        bodyOutput += "                    <td class='border px-4 py-2'>" + post.title + "</td>\n";
        bodyOutput += "                </tr>\n";
        bodyOutput += "            </tbody>\n";
        bodyOutput += "        </table>\n";
        bodyOutput += "    </div>\n"; // End of scrollable container

        bodyOutput += "</div>\n"; // End of main container

        setBody(bodyOutput);
    }

}