#include "jsonparser.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

bool JSONParser::isNumeric(const std::string &str)
{
    std::size_t chr(0);

    int numCnt, ptCnt;
    for (numCnt = 0, ptCnt = 0; std::isdigit(str[chr]) || str[chr] == '.'; ++chr) {
        str[chr] == '.' ? ++ptCnt : ++numCnt;
    }

    if (ptCnt > 1 || numCnt < 1) {
        return false;
    }

    return chr == str.size();
}

std::string JSONParser::getData(const std::string &line)
{
    int firstNonSpace = line.find_first_not_of(' ');
    int lastNonSpace = line.find_last_not_of(' ');

    if (line.at(firstNonSpace) == '\"' && line.at(lastNonSpace) == '\"') {
        return line.substr(firstNonSpace + 1, lastNonSpace - (firstNonSpace + 1));
    }
    else if (line.at(firstNonSpace) != '\"' && line.at(lastNonSpace) != '\"') {
        std::string data = line.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        if (!isNumeric(data)) {
            throw std::runtime_error("Invalid data type: " + data);
        }
        return data;
    }

    throw std::runtime_error("Invalid data format: " + line);
}

std::map<std::string, std::string> JSONParser::Parse(std::istream &iStream)
{
    std::map<std::string, std::string> parsedData;
    std::string line;

    while (std::getline(iStream, line)) {
        if (line.find(":") != std::string::npos) {
            if (line.back() == ',') { line.pop_back(); }

            std::string key = getData(line.substr(0, line.find(":")));

            std::vector<std::string> validKeys{"name", "hp", "dmg"};
            if (std::find(std::begin(validKeys), std::end(validKeys), key) == std::end(validKeys)) {
                throw std::runtime_error("Invalid key: " + key);
            }

            std::string value = getData(line.substr(line.find(":") + 1));

            parsedData.insert(std::pair<std::string, std::string>(key, value));
        }
    }

    return parsedData;
}

std::map<std::string, std::string> JSONParser::Parse(const std::string &iString)
{
    std::ifstream fileStream(iString);

    if (fileStream.good() && fileStream.is_open()) {
        return Parse(fileStream);
    }

    std::istringstream stringStream(iString);
    return Parse(stringStream);
}
