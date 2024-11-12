#include "header.comp.h"
#include <sstream>
#include "../../Helpers/Session/session.h"

namespace Views
{
    Header::Header(std::shared_ptr<cgicc::Cgicc> _cgi): cgi(_cgi) {};

    std::ostream& operator<<(std::ostream& os, const Header& nav)
    {
        // Create an output string stream for building the header HTML
        std::ostringstream output_text;    
        output_text << "<header class=\"bg-gray-200 shadow\">\n";
        output_text << "  <div class=\"max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8\">\n";
        output_text << "    <h1 class=\"text-3xl font-bold text-gray-900\">don't README.md</h1>\n";

        // Check if the user is logged in
        if (Session::userId(nav.cgi).has_value())
        {
            // Print the Logout header
            output_text << "    <div class=\"mt-4\">\n";
            output_text << "      <a href=\"/logout\" class=\"text-blue-600 hover:text-blue-800\">Logout</a>\n";
            output_text << "    </div>\n";
        }

        output_text << "  </div>\n";
        output_text << "</header>\n";

        // Output the constructed HTML to the provided ostream
        os << output_text.str();
        
        return os; 
    }
}