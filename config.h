#ifndef CONFIG_H
#define CONFIG_H

#define HOST_ADDRESS "http://172.27.21.242"

// Config file for the entire project
#define DB_CONNECTION_USERNAME "admin"
#define DB_CONNECTION_PASSWORD "admin"

// Models
#define FIRST_NAME_LENGTH 50
#define LAST_NAME_LENGTH 50
#define EMAIL_LENGTH 100
#define PASSWORD_HASH_LENGTH 255
#define PERMISSIONS_LEVEL_LENGTH 20

// Session
// Must be even number to convert to hex
#define SESSION_TOKEN_SIZE 256

// Seconds for use, is a day long, 24 hours * 60 minutes * 60 seconds
#define TOKEN_EXPIRY_TIME 24*60*60

// Logs
#define LOG_FILE_LOCATION "/var/log/blog_app.log"

// Email
#define PAYLOAD_TEXT_SIZE 1024
#define EMAIL_FROM_ADDRESS "no-reply@dontreadme.com"

#endif
