#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../../env.h"
#include "../../Logger/logger.h"
#include "../../Controllers/Seeding/seed.h"
#include "../../Helpers/Database/db_connection.h"
#include "../../Helpers/Email/email.h"

#define EMAIL_TO "<recipient_email@example.com>"


int main() {
    Logger::logInfo("Initializing email sending process...");
    Email::EmailMessage message;
    message.from = "test@test.com";
    message.to = "test@test.com";
    message.subject = "test";
    message.body = "test";

    Email::sendEmail(message);
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::seed(cgi).render();
    return EXIT_SUCCESS;
}