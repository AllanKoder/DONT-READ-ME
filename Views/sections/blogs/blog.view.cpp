#include "blog.view.h"
#include <sstream>
#include <vector>

namespace Views
{
    Blog::Blog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post) : View(cgi)
    {
        setTitle("Blog: " + post.title);
        std::string bodyOutput;


        // Blog post details
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";
        bodyOutput += "    <h1 class='text-3xl font-bold mb-4'>" + post.title + "</h1>\n";
        bodyOutput += "    <p class='text-gray-600 mb-2'>By <strong>" + post.username + "</strong> on " + post.dateCreated + "</p>\n";

        // Upvote and Downvote forms
        bodyOutput += "    <div class='flex items-center mb-0'>\n";
        // Vote count display
        bodyOutput += "        <span class='text-lg p-3'>" + std::to_string(post.upvotes) + " Upvotes</span>\n";

        // Upvote form
        bodyOutput += "        <form action='/cgi-bin/upvote.cgi' method='POST' class='mr-2'>\n";
        bodyOutput += "            <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n"; // Assuming post.id exists
        bodyOutput += "            <button type='submit' class='bg-blue-500 text-white rounded-md px-4 py-2 hover:bg-blue-600 transition'>Upvote</button>\n";
        bodyOutput += "        </form>\n";

        // Downvote form
        bodyOutput += "        <form action='/cgi-bin/downvote.cgi' method='POST'>\n";
        bodyOutput += "            <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n"; // Assuming post.id exists
        bodyOutput += "            <button type='submit' class='bg-red-500 text-white rounded-md px-4 py-2 hover:bg-red-600 transition'>Downvote</button>\n";
        bodyOutput += "        </form>\n";

        bodyOutput += "    </div>\n"; // End of vote buttons
        bodyOutput += "    <p class='mb-6 text-lg'>" + post.content + "</p>\n"; // Content of the blog post

        // End of main container
        bodyOutput += "</div>\n";

        setBody(bodyOutput);
    }
}