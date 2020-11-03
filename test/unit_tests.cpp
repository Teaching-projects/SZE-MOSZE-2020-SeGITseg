#include "../jsonparser.h"
#include "../unit.h"
#include <fstream>
#include <cmath>

#include <gtest/gtest.h>

TEST(unitTests, test_iStream)
{
    std::ifstream iStream("../units/unit_2.json");
    std::map<std::string, std::string> expectedData{
        {"name", "Sally"},
        {"hp", "140"},
        {"dmg", "30"},
        {"cd", "1.5"}};
    std::map<std::string, std::string> data = JSONParser::ParseStream(iStream);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_iString)
{
    std::string iString = "../units/unit_1.json";
    std::map<std::string, std::string> expectedData{
        {"name", "Maple"},
        {"hp", "200"},
        {"dmg", "60"},
        {"cd", "2"}};
    std::map<std::string, std::string> data = JSONParser::ParseFile(iString);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_whitespaces)
{
    std::string fileName = "../units/test_units/valid_unit_1.json";
    std::map<std::string, std::string> expectedData{
        {"name", "Valid Unit #1"},
        {"hp", "100"},
        {"dmg", "20"},
        {"cd", "1"}};
    std::map<std::string, std::string> data = JSONParser::ParseFile(fileName);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_changedJSONorder)
{
    std::string fileName = "../units/test_units/valid_unit_2.json";
    std::map<std::string, std::string> expectedData{
        {"name", "Valid Unit #2"},
        {"hp", "100"},
        {"dmg", "20"},
        {"cd", "1"}};
    std::map<std::string, std::string> data = JSONParser::ParseFile(fileName);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(unitTests, test_invalidKey)
{
    const std::string expectedErrorMsg = "Invalid key: nev";
    std::ifstream invalidInput("../units/test_units/invalid_unit_1.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {
        ASSERT_EQ(e.what(), expectedErrorMsg);
    }
}

TEST(unitTests, test_invalidDataFormat)
{
    const std::string expectedErrorMsg = "Invalid data format:  \"20";
    std::ifstream invalidInput("../units/test_units/invalid_unit_2.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_invalidDataType)
{
    const std::string expectedErrorMsg = "Invalid data type:  \"1.0.1\"";
    std::ifstream invalidInput("../units/test_units/invalid_unit_3.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_missingJSON)
{
    const std::string expectedErrorMsg = "Error while opening file: missingJSON.json";
    std::ifstream missingFile("../missingJSON.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(missingFile);
    }
    catch (std::runtime_error &e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(unitTests, test_fight)
{
    Unit A = Unit::parseUnit("../units/unit_1.json");
    Unit B = Unit::parseUnit("../units/unit_2.json");

    A.fight(B);

    ASSERT_TRUE(A.getHp() == 0 || B.getHp() == 0);
}

TEST(unitTests, test_level)
{
    Unit A = Unit::parseUnit("../units/unit_1.json");
    Unit B = Unit::parseUnit("../units/unit_2.json");

    A.fight(B);

    ASSERT_EQ(A.getLvl(), 2);
    ASSERT_EQ(B.getLvl(), 1);
}

TEST(unitTests, test_levelUpStats)
{
    Unit A = Unit::parseUnit("../units/unit_1.json");
    Unit B = Unit::parseUnit("../units/unit_3.json");

    int expectedDmg = round(A.getDmg() * 1.1);
    int expectedHp = round(A.getHp() * 1.1);

    A.fight(B);

    ASSERT_EQ(A.getDmg(), expectedDmg);
    ASSERT_EQ(A.getHp(), expectedHp);
}

TEST(unitTests, test_getters)
{
    Unit A = Unit::parseUnit("units/unit_1.json");

    ASSERT_EQ(A.getName(), "Maple");
    ASSERT_EQ(A.getHp(), 200);
    ASSERT_EQ(A.getDmg(), 60);
    ASSERT_EQ(A.getCd(), 2);
    ASSERT_EQ(A.getLvl(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
