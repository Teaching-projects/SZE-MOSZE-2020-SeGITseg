#include "../unit.h"
#include <cmath>

#include <gtest/gtest.h>

TEST(unitTest, test_fight)
{
    Unit A = Unit::parseUnit("units/unit_1.json");
    Unit B = Unit::parseUnit("Units/unit_2.json");

    A.fight(B);

    ASSERT_TRUE(A.getHp() == 0 || B.getHp() == 0);
}

TEST(unitTest, test_level)
{
    Unit A = Unit::parseUnit("units/unit_1.json");
    Unit B = Unit::parseUnit("units/unit_2.json");

    A.fight(B);

    ASSERT_EQ(A.getLvl(), 2);
    ASSERT_EQ(B.getLvl(), 1);
}

TEST(unitTest, test_levelUpStats)
{
    Unit A = Unit::parseUnit("units/unit_1.json");
    Unit B = Unit::parseUnit("units/unit_3.json");

    int expectedDmg = round(A.getDmg() * 1.1);
    int expectedHp = round(A.getHp() * 1.1);

    A.fight(B);

    ASSERT_EQ(A.getDmg(), expectedDmg);
    ASSERT_EQ(A.getHp(), expectedHp);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}