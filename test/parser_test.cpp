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

TEST(parserTest, test_whitespaces)
{
    std::string fileName = "units/test_units/valid_unit_1.json";
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

TEST(parserTest, test_invalidKey)
{
    const std::string expectedErrorMsg = "Invalid key: nev";
    std::ifstream invalidInput("units/test_units/invalid_unit_1.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {
        ASSERT_EQ(e.what(), expectedErrorMsg);
    }
}

TEST(parserTest, test_invalidDataFormat)
{
    const std::string expectedErrorMsg = "Invalid data format:  \"20";
    std::ifstream invalidInput("units/test_units/invalid_unit_2.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

TEST(parserTest, test_invalidDataType)
{
    const std::string expectedErrorMsg = "Invalid data type:  \"1.0.1\"";
    std::ifstream invalidInput("units/test_units/invalid_unit_3.json");
    try {
        std::map<std::string, std::string> data = JSONParser::ParseStream(invalidInput);
    }
    catch (std::runtime_error &e) {	
        ASSERT_EQ(e.what(), expectedErrorMsg);	
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}