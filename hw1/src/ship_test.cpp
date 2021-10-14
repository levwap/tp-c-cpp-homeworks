#include <gtest/gtest.h>
extern "C" {
#include "ship.h"
#include "ship.c"
}


TEST(create_ship, Compare) {
    EXPECT_EQ(0, NO_INFORMATION);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
