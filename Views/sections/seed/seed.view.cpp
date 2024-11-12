#include "seed.view.h"

namespace Views
{
    Seed::Seed(std::shared_ptr<cgicc::Cgicc> cgi) : View(cgi)
    {

        setTitle("seed()");
        setBody("seeded()");
    }
}