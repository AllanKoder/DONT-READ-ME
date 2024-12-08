#include <string>

namespace Email
{
    /**
     * @brief Structure representing an email message.
     */
    struct EmailMessage
    {
        std::string to;      // The recipient's email address.
        std::string subject; // The subject line of the email.
        std::string body;    // The body content of the email.
    };

    /**
     * @brief Sends an email message.
     * 
     * This function takes an EmailMessage structure and sends it to the specified recipient.
     * 
     * @param email The EmailMessage object containing the details of the email to be sent.
     */
    void sendEmail(const EmailMessage& email);
}