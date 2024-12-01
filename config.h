#ifndef CONFIG_H
#define CONFIG_H

// IP
#define HOST_ADDRESS "http://172.27.21.242"

// LOGIN
#define MAX_CODE_ATTEMPTS 3
// In Seconds (5 minutes), 5 minutes. 60 seconds * 5 minutes
#define PENDING_TOKEN_EXPIRY_TIME 60*5

// MODELS
#define FIRST_NAME_LENGTH 50
#define LAST_NAME_LENGTH 50
#define EMAIL_LENGTH 100
#define PASSWORD_HASH_LENGTH 255
#define PERMISSIONS_LEVEL_LENGTH 20

// SESSION
// Must be even number to convert to hex
#define SESSION_TOKEN_SIZE 256
// In Seconds (20 minutes), 20 minutes * 60 seconds
#define TOKEN_EXPIRY_TIME 20*60

// LOGS
#define LOG_FILE_LOCATION "/var/log/blog_app.log"

// EMAIL
#define PAYLOAD_TEXT_SIZE 1024
#define EMAIL_FROM_ADDRESS "no-reply@dontreadme.com"

#endif
