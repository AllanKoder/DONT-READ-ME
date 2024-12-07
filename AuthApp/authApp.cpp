#include <iostream>
#include "../env.h"
#include "../Helpers/Cryptography/crypto.h"

// The application which shows the code for admin login
int main()
{
    std::cout << "App Code is: " << Crypto::getAppCode() << "\n";
}