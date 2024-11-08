#ifndef LOGGER_H
#define LOGGER_H

#include <string>
namespace Logger
{
    void logInfo(std::string info);
    void logWarning(std::string info);
    void logCritical(std::string info);
}

#endif
