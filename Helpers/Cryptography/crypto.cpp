#include "crypto.h"
#include "../../env.h"
#include "../../config.h"
#include <crypto++/cryptlib.h>
#include <crypto++/sha.h>
#include <crypto++/hmac.h>
#include <crypto++/hex.h>
#include <crypto++/rdrand.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cstddef>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace Crypto
{
    std::string hash(const std::string& data, const std::string& salt) {
        // Combine data and salt
        std::string combined = HASH_KEY + data + salt;

        // Prepare for hashing
        CryptoPP::byte abDigest[CryptoPP::SHA256::DIGESTSIZE];
        CryptoPP::SHA256 hash;

        // Calculate the digest
        hash.CalculateDigest(abDigest, reinterpret_cast<const CryptoPP::byte*>(combined.data()), combined.size());

        // Encode the digest to a hex string
        std::string hexDigest;
        CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexDigest));
        encoder.Put(abDigest, sizeof(abDigest));
        encoder.MessageEnd();

        return hexDigest; // Return the hexadecimal representation of the digest
    }

    std::string hmac(const std::string& data)
    {
        // Create HMAC object
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(
            reinterpret_cast<const CryptoPP::byte*>(SECRET_KEY), 
            strlen(SECRET_KEY)
        );

        // Calculate HMAC
        CryptoPP::byte abDigest[CryptoPP::HMAC<CryptoPP::SHA256>::DIGESTSIZE];
        hmac.CalculateDigest(abDigest, reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size());

        // Encode the digest to a hex string
        std::string hexDigest;
        CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexDigest));
        encoder.Put(abDigest, sizeof(abDigest));
        encoder.MessageEnd();

        return hexDigest;
    }

    std::string getRandomToken()
    {
        // Turn the SESSION_TOKEN_SIZE to the the byte length (which is smaller when converted to string again)
        const std::size_t tokenLength = (int)((SESSION_TOKEN_SIZE)/2);

        // Turning to hex will make the size double
        std::array<CryptoPP::byte, tokenLength> randomBytes;

        // Use AutoSeededRandomPool for secure random number generation
        CryptoPP::AutoSeededRandomPool rng;
        rng.GenerateBlock(randomBytes.data(), randomBytes.size());

        // Convert random bytes to hex string
        std::string token;
        CryptoPP::HexEncoder hexEncoder(new CryptoPP::StringSink(token));
        hexEncoder.Put(randomBytes.data(), randomBytes.size());
        hexEncoder.MessageEnd();

        return token;
    }

    std::string getRandomSixCharCode()
    {
        const std::size_t tokenLength = 3;

        // Turning to hex will make the size double
        std::array<CryptoPP::byte, tokenLength> randomBytes;

        // Use AutoSeededRandomPool for secure random number generation
        CryptoPP::AutoSeededRandomPool rng;
        rng.GenerateBlock(randomBytes.data(), randomBytes.size());

        // Convert random bytes to hex string
        std::string token;
        CryptoPP::HexEncoder hexEncoder(new CryptoPP::StringSink(token));
        hexEncoder.Put(randomBytes.data(), randomBytes.size());
        hexEncoder.MessageEnd();

        return token;
    }

    std::string getCurrentTimeRounded30Seconds() {
        static std::string cachedTime;
        static auto lastUpdate = std::chrono::steady_clock::now();

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();

        if (duration >= 30 || cachedTime.empty()) {
            auto timePoint = std::chrono::system_clock::now();
            auto timeT = std::chrono::system_clock::to_time_t(timePoint);
            std::tm timeInfo = *std::localtime(&timeT);

            // Round down to nearest 30 seconds
            timeInfo.tm_sec = (timeInfo.tm_sec / 30) * 30;

            std::ostringstream oss;
            oss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
            cachedTime = oss.str();
            lastUpdate = now;
        }

        return cachedTime;
    }

    std::string getAppCode()
    {
        return hash(getCurrentTimeRounded30Seconds(), AUTH_APP_KEY).substr(0, 2);
    }
}