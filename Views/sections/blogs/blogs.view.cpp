#include "blogs.view.h"

namespace Views
{
    Blogs::Blogs(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {
        setTitle("Blogs");
        setBody("<h1>Blogs Title</h1>");
    }
}