#include "email.h"  
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../../Logger/logger.h"
#include "../../env.h"
#include "../../config.h"

char payload_text[6][PAYLOAD_TEXT_SIZE]; // Allocate a fixed size for each entry

struct upload_status {
    int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if (upload_ctx->lines_read >= static_cast<size_t>(sizeof(payload_text) / sizeof(payload_text[0]))) {
        return 0;  // End of payload
    }

    data = payload_text[upload_ctx->lines_read++];
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    return len;  // Return number of bytes copied
}

void Email::sendEmail(const EmailMessage& email) {
    Logger::logInfo("Initializing email sending process...");

    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx = {0};

    // Prepare the payload text
    snprintf(payload_text[0], PAYLOAD_TEXT_SIZE, "Date: Mon, 29 Nov 2024 21:54:29 +0000\r\n");
    snprintf(payload_text[1], PAYLOAD_TEXT_SIZE, "To: %s\r\n", email.to.c_str());
    snprintf(payload_text[2], PAYLOAD_TEXT_SIZE, "From: %s\r\n", email.from.c_str());
    snprintf(payload_text[3], PAYLOAD_TEXT_SIZE, "Subject: %s\r\n", email.subject.c_str());
    snprintf(payload_text[4], PAYLOAD_TEXT_SIZE, "\r\n");  // Blank line separating headers from body
    snprintf(payload_text[5], PAYLOAD_TEXT_SIZE, "%s\r\n", email.body.c_str());

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set SMTP server URL
        char smtp_url[256];
        snprintf(smtp_url, sizeof(smtp_url), "%s:%s", EMAIL_SERVER_HOST, EMAIL_SERVER_PORT);
        Logger::logInfo("Using SMTP server: " + std::string(smtp_url));
        
        curl_easy_setopt(curl, CURLOPT_URL, smtp_url);
        
        // Set the sender's email address
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, email.from.c_str());
        
        // Add recipient email address
        recipients = curl_slist_append(recipients, email.to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        
        // Specify the payload source and read function
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Set username and password for authentication
        curl_easy_setopt(curl, CURLOPT_USERNAME, EMAIL_SERVER_USER);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, EMAIL_SERVER_PASSWORD);

        // Enable verbose output for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the email sending operation
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            Logger::logCritical("Email sending failed: " + std::string(curl_easy_strerror(res)));
        } else {
            Logger::logInfo("Email sent successfully.");
        }

        // Clean up
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    } else {
        Logger::logCritical("Failed to initialize CURL.");
    }
    
    curl_global_cleanup();
}

