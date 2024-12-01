#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <array>

namespace Crypto
{
    std::string hash(const std::string& data, const std::string& salt);
    std::string getRandomToken();
    std::string getRandomSixCharCode();
    std::string hmac(const std::string& data);
    // 2 character long code that regenerates every 30 seconds
    std::string getAppCode();
}
#endif
