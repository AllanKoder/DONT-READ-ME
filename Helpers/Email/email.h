
#include <string>

namespace Email
{
    struct EmailMessage
    {
        std::string to;
        std::string subject;
        std::string body;
    };

    void sendEmail(const EmailMessage& email);
}