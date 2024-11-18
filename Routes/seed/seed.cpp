#include "../../Logger/logger.h"
#include "../../Controllers/Seeding/seed.h"
#include "../../Helpers/Database/db_connection.h"

// /seed.cgi
int main()
{
    auto cgi = std::make_shared<cgicc::Cgicc>();
    Controllers::seed(cgi).render();
    return EXIT_SUCCESS;
}
