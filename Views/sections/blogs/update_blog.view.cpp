#include "update_blog.view.h"
#include "../../../Helpers/Session/session.h"
#include "../../../Helpers/String/string_helpers.h"
#include "../../components/csrf_token.comp.h"
#include <sstream>
#include <vector>

namespace Views
{
    UpdateBlog::UpdateBlog(std::shared_ptr<cgicc::Cgicc> cgi, Database::Requests::BlogModel post) : View(cgi)
    {
        setTitle("Update Blog");

        std::string bodyOutput;
        // Main container for the form
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";
        
        // Form for updating a blog
        bodyOutput += "    <form action='/cgi-bin/updateBlogPost.cgi/" + std::to_string(post.id) + "' method='POST' class='space-y-4'>\n";
        bodyOutput += "        <label for='title' class='block text-lg font-medium text-gray-700'>Title</label>\n";
        bodyOutput += "        <input type='text' name='title' id='title' value='" + StringHelpers::htmlSpecialChars(post.title) + "' class='border rounded-md p-2 w-full' required />\n";

        bodyOutput += "        <label for='content' class='block text-lg font-medium text-gray-700'>Content</label>\n";
        bodyOutput += "        <textarea name='content' id='content' class='border rounded-md p-2 w-full' rows='5' required>" + StringHelpers::htmlSpecialChars(post.content) + "</textarea>\n";

        // CSRF Token
        bodyOutput += CsrfToken(cgi).Render();

        // Hidden input for the post ID
        bodyOutput += "        <input type='hidden' name='post_id' value='" + std::to_string(post.id) + "' />\n";

        bodyOutput += "        <button type='submit' class='bg-blue-500 text-white rounded-md p-2'>Update</button>\n";
        bodyOutput += "    </form>\n";

        bodyOutput += "</div>\n"; // End of main container

        setBody(bodyOutput);
    }
}