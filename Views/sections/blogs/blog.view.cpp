#include "blog.view.h"
#include "../../../Helpers/Session/session.h"
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

        // Edit blog (if creator)
        bodyOutput += "<div class='flex flex-row items-center gap-3'>\n";
        bodyOutput += "    <h1 class='text-3xl font-bold'>" + StringHelpers::htmlSpecialChars(post.title) + "</h1>\n";

        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() && userInfo.value().id == post.userId)
        {
            bodyOutput += "    <button class='text-gray-600 hover:text-gray-800 focus:outline-none'>\n";
            bodyOutput += "        <svg class='w-5 h-5' fill='none' stroke='currentColor' viewBox='0 0 24 24' xmlns='http://www.w3.org/2000/svg'>\n";
            bodyOutput += "            <path stroke-linecap='round' stroke-linejoin='round' stroke-width='2' d='M15.232 5.232l3.536 3.536m-2.036-5.036a2.5 2.5 0 113.536 3.536L6.5 21.036H3v-3.572L16.732 3.732z'></path>\n";
            bodyOutput += "        </svg>\n";
            bodyOutput += "    </button>\n";
        }
        bodyOutput += "</div>\n";

        // Username
        bodyOutput += "    <p class='text-gray-600 mb-2'>By <strong>" + StringHelpers::htmlSpecialChars(post.username) + "</strong> on " + post.dateCreated + "</p>\n";

        // Upvote
        bodyOutput += "<div class='flex items-center'>\n";
        bodyOutput += "    <div class='flex flex-row items-stretch border border-gray-300 rounded-md overflow-hidden h-6 mb-4'>\n";
        bodyOutput += "        <form hx-post='/cgi-bin/upvoteBlog.cgi/" + std::to_string(post.id) + "' \
                                hx-target='#upvotes-counter' hx-select='#upvotes-counter' hx-swap='outerHTML' class='h-full'>\n";
        bodyOutput += CsrfToken(cgi).Render();
        bodyOutput += "            <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n";
        bodyOutput += "            <button type='submit' class='bg-gray-100 hover:bg-gray-200 transition h-full px-1 text-gray-600 flex items-center justify-center'>\n";
        bodyOutput += "                <svg class='w-4 h-4' fill='currentColor' viewBox='0 0 20 20'>\n";
        bodyOutput += "                    <path fill-rule='evenodd' d='M14.707 12.707a1 1 0 01-1.414 0L10 9.414l-3.293 3.293a1 1 0 01-1.414-1.414l4-4a1 1 0 011.414 0l4 4a1 1 0 010 1.414z' clip-rule='evenodd'></path>\n";
        bodyOutput += "                </svg>\n";
        bodyOutput += "            </button>\n";
        bodyOutput += "        </form>\n";

        // Votes
        bodyOutput += "        <div id='upvotes-counter' class='px-3 flex items-center justify-center bg-white text-center min-w-[2rem]'>" + std::to_string(post.upvotes) + "</div>\n";

        bodyOutput += "        <form hx-post='/cgi-bin/downvoteBlog.cgi/" + std::to_string(post.id) + "' \
                                hx-target='#upvotes-counter' hx-select='#upvotes-counter' hx-swap='outerHTML' class='h-full'>\n";
        bodyOutput += CsrfToken(cgi).Render();
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