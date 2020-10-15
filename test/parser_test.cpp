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
    std::map<std::string, std::string> data = JSONParser::Parse(iStream);

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
    std::map<std::string, std::string> data = JSONParser::Parse(iString);

    for (auto e : expectedData)
    {
        ASSERT_EQ(data[e.first], e.second);
    }
}

TEST(parserTest, test_invalidInput)
{
    const std::string expectedError = "Invalid key: nev";
    std::ifstream invalidInput("units/invalid_unit.json");
    try
    {
        std::map<std::string, std::string> data = JSONParser::Parse(invalidInput);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error &e)
    {
        ASSERT_EQ(e.what(), expectedError);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}