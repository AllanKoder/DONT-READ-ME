#include "blog.view.h"
#include "../../../Helpers/String/string_helpers.h"
#include "../../components/csrf_token.comp.h"
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
        bodyOutput += "    <h1 class='text-3xl font-bold mb-4'>" + StringHelpers::htmlSpecialChars(post.title) + "</h1>\n";
        // Username
        bodyOutput += "    <p class='text-gray-600 mb-2'>By <strong>" + StringHelpers::htmlSpecialChars(post.username) + "</strong> on " + post.dateCreated + "</p>\n";

        // Upvote
        bodyOutput += "<div class='flex items-center'>\n";
        bodyOutput += "    <div class='flex flex-row items-stretch border border-gray-300 rounded-md overflow-hidden h-6 mb-4'>\n";
        bodyOutput += "        <form action='/cgi-bin/upvote.cgi' method='POST' class='h-full'>\n";
        bodyOutput +=             CsrfToken(cgi).Render();
        bodyOutput += "            <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n";
        bodyOutput += "            <button type='submit' class='bg-gray-100 hover:bg-gray-200 transition h-full px-1 text-gray-600 flex items-center justify-center'>\n";
        bodyOutput += "                <svg class='w-4 h-4' fill='currentColor' viewBox='0 0 20 20'>\n";
        bodyOutput += "                    <path fill-rule='evenodd' d='M14.707 12.707a1 1 0 01-1.414 0L10 9.414l-3.293 3.293a1 1 0 01-1.414-1.414l4-4a1 1 0 011.414 0l4 4a1 1 0 010 1.414z' clip-rule='evenodd'></path>\n";
        bodyOutput += "                </svg>\n";
        bodyOutput += "            </button>\n";
        bodyOutput += "        </form>\n";
        bodyOutput += "        <div class='px-3 flex items-center justify-center bg-white text-center min-w-[2rem]'>" + std::to_string(post.upvotes) + "</div>\n";
        bodyOutput += "        <form action='/cgi-bin/downvote.cgi' method='POST' class='h-full'>\n";
        bodyOutput +=             CsrfToken(cgi).Render();
        bodyOutput += "            <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n";
        bodyOutput += "            <button type='submit' class='bg-gray-100 hover:bg-gray-200 transition h-full px-1 text-gray-600 flex items-center justify-center'>\n";
        bodyOutput += "                <svg class='w-4 h-4' fill='currentColor' viewBox='0 0 20 20'>\n";
        bodyOutput += "                    <path fill-rule='evenodd' d='M5.293 7.293a1 1 0 011.414 0L10 10.586l3.293-3.293a1 1 0 111.414 1.414l-4 4a1 1 0 01-1.414 0l-4-4a1 1 0 010-1.414z' clip-rule='evenodd'></path>\n";
        bodyOutput += "                </svg>\n";
        bodyOutput += "            </button>\n";
        bodyOutput += "        </form>\n";
        bodyOutput += "    </div>\n";
        bodyOutput += "</div>\n";

        // Content
        bodyOutput += "    <p class='mb-6 text-lg'>" + StringHelpers::htmlSpecialChars(post.content) + "</p>\n"; // Content of the blog post

        // End of main container
        bodyOutput += "</div>\n";

        setBody(bodyOutput);
    }
}