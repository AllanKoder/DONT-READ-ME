#include "views.h"
#include <iostream>
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPRedirectHeader.h>
#include <sstream>
#include "components/header.comp.h"
#include <string>
#include <string.h>
#include "../Helpers/String/string_helpers.h"
#include "../Helpers/Request/request.h"
#include "../Logger/logger.h"

namespace Views
{
    View::View(std::shared_ptr<cgicc::Cgicc> _cgi) : redirectUrl(""), body(""), headers(""), cgi(_cgi)
    {
        title = "No Title";
        cookies.clear();
    }

    std::string View::getHeader()
    {
        std::ostringstream outputHeader;

        if (!redirectUrl.empty())
        {
            // There is a redirect, set it as the header
            outputHeader << "Status: 302 Found\n";
            outputHeader << "Location: " << redirectUrl << "\n";
        }
        else
        {
            // If there's no redirect, proceed with the normal header
            outputHeader << "Content-Type: text/html\n";
        }

        // Add custom headers
        outputHeader << headers;

        // Add cookies
        for (const auto &cookie : cookies)
        {
            outputHeader << "Set-Cookie: " << cookie << "\n";
        }

        outputHeader << "\n";
        return outputHeader.str();
    }

    void View::getNotifications()
    {
        std::string notifValue = Request::getQueryValue("notification", cgi->getEnvironment().getQueryString());
        if (!notifValue.empty())
        {
            // Split by pipe '|' to separate type and message
            std::vector<std::string> parts = StringHelpers::split(notifValue, "|");

            // Check if there's a message after the '|'
            if (parts.size() == 2)
            {
                std::string type = parts[0];
                std::string message = parts[1];
                message = StringHelpers::urlDecode(message); // Decode the message

                // Display notification using Notyf
                if (type == "Success")
                {
                    std::cout << "notyf.success('" << message << "');\n";
                }
                else if (type == "Warning")
                {
                    std::cout << "notyf.error('" << message << "');\n";
                }
            }
        }
    }

    View &View::setNotification(NotificationType type, const std::string &message)
    {
        // Create a notification string in the format "Type|Message"
        std::string notificationQuery;
        notificationQuery = (type == NotificationType::SUCCESS ? "Success" : "Warning") + std::string("|") + message;

        // Append to redirect URL as a query parameter
        if (redirectUrl.find('?') != std::string::npos)
        {
            redirectUrl += "&notification=" + notificationQuery;
        }
        else
        {
            redirectUrl += "?notification=" + notificationQuery;
        }

        return *this;
    }

    void View::render()
    {
        // Output HTTP headers
        std::cout << getHeader() << "\n";

        if (redirectUrl.empty())
        {
            // Start HTML document
            std::cout << "<html lang=\"en\" class=\"h-full\">\n";

            // Start the <head>
            std::cout << "<head>\n";
            std::cout << "<meta charset=\"UTF-8\">\n";
            std::cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
            std::cout << "<title>" << title << "</title>\n";
            std::cout << "<script src=\"https://cdn.tailwindcss.com\"></script>\n";
            std::cout << "<script src=\"https://unpkg.com/htmx.org@2.0.3\"></script>\n";

            std::cout << "<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.css\">\n";
            std::cout << "</head>\n";

            // Start the body
            std::cout << "<body class=\"h-full bg-white\">\n";
            std::cout << "<script src=\"https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.js\"></script>\n";

            // Header component
            std::cout << Views::Header(cgi).Render();

            // Initialize Notyf
            std::cout << "<script>\n";
            std::cout << "var notyf = new Notyf({\
            position: {\
                x: 'center',\
                y: 'top',\
            }});\n";

            getNotifications(); // Call to get notifications

            std::cout << "</script>\n";

            // Main content
            std::cout << "<main class=\"flex items-center justify-center h-5/6\">\n";
            std::cout << "  <div class=\"max-w-7xl mx-auto py-6 sm:px-6 lg:px-8\">\n";
            std::cout << "    <div class=\"px-4 py-6 sm:px-0\">\n";

            // Updated card styling
            std::cout << "      <div id=\"content-body\" class=\"border rounded-lg min-h-[200px] min-w-[300px] p-6 shadow-lg bg-white flex items-center justify-center\">\n";

            // Body content
            std::cout << body;

            std::cout << "      </div>\n";

            std::cout << "    </div>\n";
            std::cout << "  </div>\n";
            std::cout << "</main>\n";

            // End HTML document
            std::cout << "</body>\n";
            std::cout << "</html>\n";
        }
    }

    View &View::setRedirect(const std::string &url)
    {
        redirectUrl = url;
        return *this;
    }

    View &View::setHeader(std::string header)
    {
        headers += header + "\r\n";
        return *this;
    }

    View &View::setCookie(std::string cookie)
    {
        cookies.push_back(cookie);
        return *this;
    }

    View &View::setBody(std::string newBody)
    {
        body = newBody;
        return *this;
    }

    View &View::setTitle(std::string newTitle)
    {
        title = newTitle;
        return *this;
    }
}