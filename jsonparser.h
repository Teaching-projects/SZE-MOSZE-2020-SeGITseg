#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <map>
#include <string>
#include <istream>

class JSONParser
{
private:
    static bool isNumeric(const std::string &input);
    static std::string getData(const std::string &line);
public:
    static std::map<std::string, std::string> Parse(std::istream &iStream);
    static std::map<std::string, std::string> Parse(const std::string &iString);
};

#endif