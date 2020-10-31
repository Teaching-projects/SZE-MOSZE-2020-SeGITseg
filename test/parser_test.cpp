#include "../jsonparser.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(parserTest, test_iStream)
{
    std::ifstream iStream("units/unit_2.json");
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

TEST(parserTest, test_iString)
{
    std::string iString = "units/unit_1.json";
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

TEST(parserTest, test_invalidInput)
{
    std::ifstream invalidInput("units/invalid_units/invalid_unit_1.json");
    ASSERT_THROW(JSONParser::ParseStream(invalidInput), std::runtime_error);
}

TEST(parserTest, test_asd)
{
    const std::string expectedErrorMsg = "Invalid data format:  \"20,";
    std::ifstream invalidInput("units/invalid_units/invalid_unit_2.json");
    try {
        std::map<std::string, std::string> data = JSONParser::Parse(invalidInput);
    }
    catch (std::runtime_error &e)	
    {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}