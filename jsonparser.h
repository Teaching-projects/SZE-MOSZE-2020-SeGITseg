/**
* \class JSONParser
*
* \brief This is the JSONParser class, which is used to parse raw JSON input.
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
    /**
	 *  \brief This is the function to parse JSON from an input stream.
	 *  \return Returns the parsed JSON in a map.
	*/
    static std::map<std::string, std::string> ParseStream(std::istream &inputStream /** [in] An istream object. */);
    /**
	 *  \brief This is the function to parse JSON from a string.
	 *  \return Returns the parsed JSON in a map.
	*/
    static std::map<std::string, std::string> ParseString(const std::string &inputString /** [in] A string object. */);
    /**
	 *  \brief This is the function to parse JSON from a file.
	 *  \return Returns the parsed JSON in a map.
	*/
    static std::map<std::string, std::string> ParseFile(const std::string &fileName /** [in] A filename object. */);
};

#endif