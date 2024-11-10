#include "../../Logger/logger.h"
#include "../../Controllers/Seeding/seed.h"
#include "../../Helpers/Database/db_connection.h"


int main()
{
    Controllers::seed().render();
    return EXIT_SUCCESS;
}
