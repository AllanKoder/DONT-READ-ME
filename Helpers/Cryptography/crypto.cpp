#include "crypto.h"
#include <iostream>
#include <string>
#include <crypto++/cryptlib.h>
#include <crypto++/sha.h>
#include <crypto++/hmac.h>
#include <crypto++/hex.h>
#include "../../env.h"
#include <cstddef>

namespace Crypto
{
    std::string hash(const std::string& data, const std::string& salt) {
        // Combine data and salt
        std::string combined = data + salt;

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

    std::array<unsigned char, 32> hmac(const std::string& data)
    {
        // Create HMAC object
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(
            reinterpret_cast<const CryptoPP::byte*>(SECRET_KEY), 
            strlen(SECRET_KEY)
        );

        // Calculate HMAC
        std::array<unsigned char, 32> mac;
        hmac.CalculateDigest(mac.data(), reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size());

        return mac;
    }
}