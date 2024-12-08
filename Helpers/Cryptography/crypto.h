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
    // 6 character code from challenge
    std::string getAppCode(std::string challenge);
}
#endif
