#include "../JSON.h"
#include "../Monster.h"
#include <fstream>
#include <cmath>
#include <any>

#include <gtest/gtest.h>

TEST(unitTests, test_iStream)
{
    std::ifstream iStream("../units/unit_2.json");
    std::map<std::string, std::string> expectedData{
        {"name", "Sally"},
        {"hp", "140"},
        {"dmg", "30"},
        {"cd", "1.5"}};
    JSON data = JSON::parseFromStream(iStream);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_iString)
{
    std::string iString = "../units/unit_1.json";
    std::map<std::string, std::any> expectedData{
        {"name", "Maple"},
        {"hp", 200},
        {"dmg", 60},
        {"cd", 2}};
    JSON data = JSON::parseFromFile(iString);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_whitespaces)
{
    std::string fileName = "../units/test_units/valid_unit_1.json";
    std::map<std::string, std::any> expectedData{
        {"name", "Valid Unit #1"},
        {"hp", 100},
        {"dmg", 20},
        {"cd", 1}};
    JSON data = JSON::parseFromFile(fileName);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_changedJSONorder)
{
    std::string fileName = "../units/test_units/valid_unit_2.json";
    std::map<std::string, std::any> expectedData{
        {"name", "Valid Unit #2"},
        {"hp", 100},
        {"dmg", 20},
        {"cd", 1}};
    JSON data = JSON::parseFromFile(fileName);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_invalidDataFormat)
{
    const std::string expectedErrorMsg = "Invalid data format:  \"20";
    std::ifstream invalidInput("../units/test_units/invalid_unit_2.json");
    try {
        JSON data = JSON::parseFromStream(invalidInput);
    }
    catch (const JSON::ParseException& e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_invalidDataType)
{
    const std::string expectedErrorMsg = "Invalid data type:  \"1.0.1\"";
    std::ifstream invalidInput("../units/test_units/invalid_unit_3.json");
    try {
        JSON data = JSON::parseFromStream(invalidInput);
    }
    catch (const JSON::ParseException& e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_missingJSON)
{
    const std::string expectedErrorMsg = "Error while opening file: missingJSON.json";
    std::ifstream missingFile("../missingJSON.json");
    try {
        JSON data = JSON::parseFromStream(missingFile);
    }
    catch (const JSON::ParseException& e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_fight)
{
    Monster A = Monster::parse("../units/unit_1.json");
    Monster B = Monster::parse("../units/unit_2.json");

    A.fightTilDeath(B);

    ASSERT_TRUE(A.getHealthPoints() == 0 || B.getHealthPoints() == 0);
}

TEST(unitTests, test_level)
{
    Monster A = Monster::parse("../units/unit_1.json");
    Monster B = Monster::parse("../units/unit_2.json");

    A.fightTilDeath(B);

    ASSERT_EQ(A.getLevel(), 2);
    ASSERT_EQ(B.getLevel(), 1);
}

TEST(unitTests, test_levelUpStats)
{
    Monster A = Monster::parse("../units/unit_1.json");
    Monster B = Monster::parse("../units/unit_3.json");

    int expectedDmg = round(A.getDamage() * 1.1);
    int expectedHp = round(A.getHealthPoints() * 1.1);

    A.fightTilDeath(B);

    ASSERT_EQ(A.getDamage(), expectedDmg);
    ASSERT_EQ(A.getHealthPoints(), expectedHp);
}

TEST(unitTests, test_getters)
{
    Monster A = Monster::parse("../units/unit_1.json");

    ASSERT_EQ(A.getName(), "Maple");
    ASSERT_EQ(A.getHealthPoints(), 200);
    ASSERT_EQ(A.getDamage(), 60);
    ASSERT_EQ(A.getAttackCoolDown(), 2);
    ASSERT_EQ(A.getLevel(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
