#include "redirect.h"
#include "../config.h"

namespace Views
{
    Redirect::Redirect(std::shared_ptr<cgicc::Cgicc> cgi, std::string url) : View(cgi)
    {
        setRedirect(HOST_ADDRESS + url);
    }
}
