#include "../jsonparser.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(parserTest, test_iStream)
{
    std::ifstream iStream("units/unit_2.json");
    std::map<std::string, std::string> expectedData{
        {"name", "Sally"},
        {"hp", "45"},
        {"dmg", "30"}};
    std::map<std::string, std::string> data = JSONParser::ParseStream(iStream);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(parserTest, test_iString)
{
    std::string iString = "units/unit_1.json";
    std::map<std::string, std::string> expectedData{
        {"name", "Maple"},
        {"hp", "150"},
        {"dmg", "10"}};
    std::map<std::string, std::string> data = JSONParser::ParseFile(iString);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(parserTest, test_invalidInput)
{
    std::ifstream invalidInput("units/invalid_unit.json");
    ASSERT_THROW(JSONParser::ParseStream(invalidInput), std::runtime_error);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}