#include <gtest/gtest.h>
#include "luckynum.h"

extern int luckynum(float money);

TEST(TEST_luckynum, IF_HASMONEY_WHEN_85_56_THEN_OK)
{
    EXPECT_EQ(luckynum(85.56), 1);
}

TEST(TEST_luckynum, IF_HASMONEY_WHEN_50_00_THEN_OK)
{
    EXPECT_EQ(luckynum(50.00), 2);
}
