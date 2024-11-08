#include "session.h"
#include "../Cryptography/hash.h"
#include "../../env.h"

namespace Session
{
    bool isValidUsernamePassword(std::string username, std::string password)
    {
        
    }

    std::string getTokenOrCreate(std::string username, std::string password);
    bool isValidToken(cgicc::CgiEnvironment environment);

}