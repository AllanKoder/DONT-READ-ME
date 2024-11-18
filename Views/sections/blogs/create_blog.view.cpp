#include "create_blog.view.h"
#include "../../../Helpers/Session/session.h"
#include "../../components/csrf_token.comp.h"
#include <sstream>
#include <vector>

namespace Views
{
    CreateBlog::CreateBlog(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        setTitle("Create Blog");

        std::string bodyOutput;
        // Main container for the form
        bodyOutput += "<div class='max-w-7xl mx-auto py-6 sm:px-6 lg:px-8'>\n";
        
        // Form for creating a blog
        bodyOutput += "    <form action='/cgi-bin/blogPost.cgi' method='POST'>\n"; // Action to handle form submission
        bodyOutput += "        <label for='title' class='block text-lg font-medium text-gray-700'>Title</label>\n";
        bodyOutput += "        <input type='text' name='title' id='title' placeholder='Enter blog title...' class='border rounded-md p-2 w-full mb-4' required />\n";

        bodyOutput += "        <label for='content' class='block text-lg font-medium text-gray-700'>Content</label>\n";
        bodyOutput += "        <textarea name='content' id='content' placeholder='Enter blog content...' class='border rounded-md p-2 w-full mb-4' rows='5' required></textarea>\n";

        // CSRF Token
        bodyOutput +=           CsrfToken(cgi).Render();

        bodyOutput += "        <button type='submit' class='bg-blue-500 text-white rounded-md p-2'>Submit</button>\n"; // Submit button
        bodyOutput += "    </form>\n";

        bodyOutput += "</div>\n"; // End of main container

        setBody(bodyOutput);
    }
}