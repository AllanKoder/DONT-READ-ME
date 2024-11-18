#include "csrf_token.comp.h"
#include <sstream>
#include "../../Helpers/Session/session.h"

namespace Views
{
    CsrfToken::CsrfToken(std::shared_ptr<cgicc::Cgicc> _cgi) : cgi(_cgi) {};

    std::string CsrfToken::Render() const
    {
        std::string output_text;
        std::string csrfToken = Session::getCsrfToken(this->cgi);
        
        // Hidden input field for CSRF token
        output_text += "<input type='hidden' name='csrf_token' value='" + csrfToken + "' />\n";

        return output_text;
    }
}