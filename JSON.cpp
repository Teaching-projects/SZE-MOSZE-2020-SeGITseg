#include "JSON.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

bool JSON::isNumeric(const std::string &str)
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

JSON JSON::parseFromStream(std::istream &inputStream)
{
  std::string fileContent = "", currentLine;
  while(std::getline(inputStream, currentLine)){
    fileContent += currentLine;
  }

  return JSON(parsetoMap(fileContent));
}

JSON JSON::parseFromString(const std::string &inputString)
{
    std::istringstream stringStream(inputString);
    return parseFromStream(stringStream);
}

JSON JSON::parseFromFile(const std::string &fileName)
{
    std::ifstream fileStream(fileName);

    if (fileStream.good() && fileStream.is_open()) {
        return parseFromStream(fileStream);
    }

    throw JSON::ParseException("Error while opening file: " + fileName);
}

jsonMap JSON::parsetoMap(const std::string &json)
{
    jsonMap mappedData;
    std::string worker = json, key, value;
    const std::regex JSONregex("\\s*\"([a-zA-Z0-9_]*)\"\\s*:\\s*(\"[a-zA-Z0-9_]*\"|\\d+.\\d+|\\d+)\\s*[,}]\\s*");
    std::smatch matches;

    while (std::regex_search(worker, matches, JSONregex))
    {
        if (matches.size() == 3)
        {
            key = matches[1].str();
            value = matches[2].str();

            if (isNumeric(value)) {
              value.find(".") == std::string::npos ? mappedData[key] = stoi(value) : mappedData[key] = stod(value);
            }
            else {
                value.erase(0, 1);
                value.erase(value.size() - 1);
                mappedData[key] = value;
            }
        }
        worker = matches.suffix();
    }
    return mappedData;
}