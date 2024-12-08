#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <cgicc/CgiEnvironment.h>
#include "cgicc/Cgicc.h"
#include <optional>
#include <memory>

namespace Session
{
    /**
     * @brief Enumeration for user privilege levels.
     */
    enum PrivilegeLevel
    {
        ADMIN,
        USER
    };

    /**
     * @brief Structure representing the result of a login attempt,
     * resulting in either a session token, or a pending session token.
     */
    struct LoginResult
    {
        bool isSessionToken;
        std::string sessionToken;
        std::string pendingSessionToken;
    };

    /**
     * @brief Structure representing user information.
     */
    struct UserInfo
    {
        int id;
        std::string username;
        PrivilegeLevel privilegeLevel;
    };

    /**
     * @brief Retrieves user information if the user is logged in.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return std::optional<UserInfo> Contains user info if logged in, otherwise nullopt.
     */
    std::optional<UserInfo> userInfo(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Deletes the session token for a given user ID.
     *
     * @param userId The ID of the user whose session token should be deleted.
     * @return bool True if the session token was successfully deleted, false otherwise.
     */
    bool deleteSessionToken(int userId);

    /**
     * @brief Attempts to log in a user with the provided credentials.
     *
     * @param username The username for login.
     * @param password The password for login.
     * @return std::optional<LoginResult> Contains a pending session token if successful, otherwise nullopt.
     */
    std::optional<LoginResult> login(std::string username, std::string password);

    /**
     * @brief Checks if the pending session token is valid.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return bool True if the pending session token is valid, false otherwise.
     */
    bool isValidPendingSessionToken(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Confirms an email code submitted by the user or admin.
     *
     * Depending on the user's privilege level, this may return an auth token or proceed to the next stage.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @param code The email code submitted by the user or admin.
     * @return std::optional<LoginResult> Contains an auth token if successful, otherwise nullopt.
     */
    std::optional<LoginResult> confirmEmailCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string code);

    /**
     * @brief Confirms an authentication code submitted by an admin only.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @param code The authentication code submitted by the admin.
     * @return std::optional<LoginResult> Contains an auth token if successful, otherwise nullopt.
     */
    std::optional<LoginResult> confirmAuthCode(std::shared_ptr<cgicc::Cgicc> cgi, std::string code);

    /**
     * @brief Retrieves the challenge code associated with a pending session token.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return std::optional<std::string> Contains the challenge code if found, otherwise nullopt.
     */
    std::optional<std::string> getChallengeCode(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Generates an anti-CSRF token for form submissions.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return std::string The generated CSRF token as a string.
     */
    std::string getCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Validates an anti-CSRF token against the current session.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return bool True if the CSRF token is valid, false otherwise.
     */
    bool isValidCsrfToken(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Checks if a given password follows security policies (e.g., length, complexity).
     *
     * @param password The password string to validate.
     * @return bool True if the password is valid according to policy, false otherwise.
     */
    bool isValidPassword(std::string password);

    /**
     * @brief Converts a string representation of privilege level to its enum equivalent.
     *
     * @param levelStr The string representation of privilege level (e.g., "ADMIN", "USER").
     * @return PrivilegeLevel The corresponding PrivilegeLevel enum value.
     */
    PrivilegeLevel stringToPrivilegeLevel(const std::string &levelStr);

    /**
     * @brief Retrieves a specific cookie value from the request context based on its name.
     *
     *@param cgi Shared pointer to a Cgicc object for CGI handling.
     *@param cookieName The name of the cookie to retrieve.
     *@return std::optional<std::string> Contains the cookie value if found, otherwise nullopt.
     */
    std::optional<std::string> getCookieToken(std::shared_ptr<cgicc::Cgicc> cgi, std::string cookieName);
}

#endif
