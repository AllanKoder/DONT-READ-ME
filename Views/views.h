#ifndef VIEWS_H
#define VIEWS_H

#include <vector>
#include <string>
#include <memory>
#include <cgicc/HTTPCookie.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/Cgicc.h>

/**
 * @brief Namespace containing view-related classes and functions.
 * 
 * The Views namespace encapsulates all components related to rendering
 * and managing HTML content in the web application.
 */
namespace Views
{
    /**
     * @brief Enumeration for different types of notifications.
     */
    enum class NotificationType
    {
        NONE,
        WARNING,
        SUCCESS,
    };

    /**
     * @brief Class representing a view in the application.
     */
    class View
    {
    private:
        std::string redirectUrl;
        std::string body;
        std::string headers;
        std::string title;
        std::vector<std::string> cookies;
        std::shared_ptr<cgicc::Cgicc> cgi;

        /**
         * @brief Get the HTTP header string.
         * @return String containing the HTTP headers.
         */
        std::string getHeader();

        /**
         * @brief Outputs the notification as a toast.
         * @return String for displaying notifications.
         */
        std::string getNotification();

    public:
        /**
         * @brief Constructor for View class.
         * @param cgi Shared pointer to Cgicc object for CGI handling.
         */
        View(std::shared_ptr<cgicc::Cgicc> cgi);

        /**
         * @brief Render the view.
         */
        void render();

        /**
         * @brief Set custom HTTP header.
         * @param header The header string to set.
         * @return Reference to this View object for method chaining.
         */
        View& setHeader(std::string header);

        /**
         * @brief Set redirect URL.
         * @param url The URL to redirect to.
         * @return Reference to this View object for method chaining.
         */
        View& setRedirect(const std::string& url);

        /**
         * @brief Set a cookie.
         * @param cookie The cookie string to set.
         * @return Reference to this View object for method chaining.
         */
        View& setCookie(std::string cookie);

        /**
         * @brief Set the page title.
         * @param newTitle The new title for the page.
         * @return Reference to this View object for method chaining.
         */
        View& setTitle(std::string newTitle);

        /**
         * @brief Set the body content of the view.
         * @param body The HTML body content.
         * @return Reference to this View object for method chaining.
         */
        View& setBody(std::string body);

        /**
         * @brief Set a notification.
         * @param type The type of notification.
         * @param message The notification message.
         * @return Reference to this View object for method chaining.
         */
        View& setNotification(NotificationType type, const std::string& message);
    };   
}

#endif