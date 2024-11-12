#include "redirect.h"

namespace Views
{
    Redirect::Redirect(std::string url)
    {
        setRedirect(url);
        setBody("<p>redirecting...</p>");
    }
}
