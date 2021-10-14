#include <gtest/gtest.h>

extern "C" {
#include "ship.h"
#include "ship.c"
}



TEST(filter, Compare) {
    ship ship0 = {"SHIP 0",
              "MOSCOW",
              2005,
              "BERLIN",
              20,
              IN_OPERATION};

    ship ship1 = {"SHIP 1",
                  "SPB",
                  2005,
                  "NEW YORK",
                  5,
                  NO_INFORMATION};

    ship ship2 = {"SHIP 2",
                  "NEW YORK",
                  2005,
                  "BERLIN",
                  100,
                  IN_OPERATION};

    ship pattern = {"",
                    "",
                    2005,
                    "",
                    0,
                    IN_OPERATION};

    ship **ships = (ship**)(malloc(sizeof(ship *) * 3));
    ships[0] = (ship*)malloc(sizeof(ship));
    ships[1] = (ship*)malloc(sizeof(ship));
    ships[2] = (ship*)malloc(sizeof(ship));
    *(ships[0]) = ship0;
    *(ships[1]) = ship1;
    *(ships[2]) = ship2;

    bool *flags = nullptr;

    filter(ships, 3, &flags, &pattern);

    EXPECT_TRUE(flags[0] == true);
    EXPECT_TRUE(flags[1] == false);
    EXPECT_TRUE(flags[2] == true);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
