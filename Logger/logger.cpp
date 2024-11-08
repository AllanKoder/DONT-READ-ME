#include <string>
#include <iostream>
#include <thread>
#include <fstream>
#include <chrono>
#include <ctime>
#include "../config.h"
#include <string.h>

namespace Logger
{
    // Write to the log file
    void write(std::string line, std::string logLevel)
    {
        const int MAX_ATTEMPTS = 5;
        const std::chrono::milliseconds RETRY_DELAY(100);

        std::ofstream logFile;
        int attempts = 0;

        // wait until open
        while (attempts < MAX_ATTEMPTS)
        {
            // Open in append form
            logFile.open(LOG_FILE_LOCATION, std::ios_base::app);

            if (logFile.is_open())
            {
                // File opened successfully
                break;
            }

            // File couldn't be opened, wait and try again
            std::this_thread::sleep_for(RETRY_DELAY);
            attempts++;
        }

        // Log is the format of LOG LEVEL:DATE AND TIME:MESSAGE
        // Display the date and time represented by the timestamp
        time_t timestamp;
        time(&timestamp);

        // remove the newline
        char *t = ctime(&timestamp);
        if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';


        // Write the line
        logFile << logLevel << " - " << t << " - " << line << std::endl;
        logFile.close();
    }

    void logInfo(std::string info)
    {
        write(info, "INFO");
    }

    void logWarning(std::string info)
    {
        write(info, "WARNING");
    }

    void logCritical(std::string info)
    {
        write(info, "CRITICAL");
    }
}