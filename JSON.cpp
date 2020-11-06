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
  std::string fileContent, currentLine;
  while(std::getline(inputStream, currentLine)){
    fileContent.append(currentLine);
  }

  return parseFromString(fileContent);
}

JSON JSON::parseFromString(const std::string &inputString)
{
    jsonMap mappedData;
    std::string worker = inputString;
    const std::regex JSONregex("\\s*\"([a-z_]*)\"\\s*:\\s*([0-9]*\\.?[0-9]+|\"[\\w\\s\\./]+\")\\s*([,}])\\s*");
    std::smatch matches;
    
    while (std::regex_search(worker, matches, JSONregex))
    {
        if (matches.size() == 4)
        {
            std::string value = matches[2].str();
            if (value.at(0) == '"')
            {
                value.erase(value.begin());
                value.erase(value.end() - 1);
                mappedData[matches[1]] = value;
            }
            else if (value.find_first_of('.') != std::string::npos)
            {
                mappedData[matches[1]] = stof(value);
            }
            else
            {
                mappedData[matches[1]] = stoi(value);
            }
        }
        worker = matches.suffix();
    }

    return JSON(mappedData);
}

JSON JSON::parseFromFile(const std::string &fileName)
{
    std::ifstream fileStream(fileName);

    if (!fileStream.good()) {
        throw JSON::ParseException("Error while opening file: " + fileName);
    }

    return parseFromStream(fileStream);
}