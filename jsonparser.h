/**
* \class Jsonparser
*
* \brief This is the Jsonparser class, which is used to input JSON files.
*
* \author Boros Dávid, Káldy Kristóf, Kreutzog András 
*
* \version 1.0
*
* \date 2020/10/15 17:30
*
* Created on: 2020/10/15 17:30
*/

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
    static std::map<std::string, std::string> ParseStream(std::istream &inputStream);
    static std::map<std::string, std::string> ParseString(const std::string &inputString);
    static std::map<std::string, std::string> ParseFile(const std::string &fileName);
};

#endif