/**
* \class JSON
*
* \brief This is the JSON class, which is used to parse raw JSON input.
*
* \author Boros Dávid, Káldy Kristóf, Kreutzog András
*
* \version 1.0
*
* \date 2020/10/15 17:30
*
* Created on: 2020/10/15 17:30
*/

#ifndef JSON_H
#define JSON_H

#include <variant>
#include <map>
#include <string>
#include <istream>
#include <algorithm>

using jsonMap = std::map<std::string, std::variant<std::string, int, double>>;

class JSON
{
private:
	jsonMap data;
	static bool isNumeric(const std::string& input);
	static jsonMap parsetoMap(const std::string &json);

public:
	JSON(jsonMap d) : data(d) {}
	/**
	 *  \brief This is the function to parse JSON from an input stream.
	 *  \return Returns the parsed JSON in a map.
	*/
	static JSON parseFromStream(std::istream& inputStream /** [in] An istream object. */);
	/**
	 *  \brief This is the function to parse JSON from a string.
	 *  \return Returns the parsed JSON in a map.
	*/
	static JSON parseFromString(const std::string& inputString /** [in] A string object. */);
	/**
	 *  \brief This is the function to parse JSON from a file.
	 *  \return Returns the parsed JSON in a map.
	*/
	static JSON parseFromFile(const std::string& fileName /** [in] A filename object. */);
	/**
	 * \class ParseException
	 * \brief This is the custom exception that is called when a parsing error occurs.
	*/
	class ParseException : public std::runtime_error
	{
	public:
		/**
		 * \brief This is the constructor of the parser exception.
		*/
		ParseException(const std::string& message /** [in] The error message. */) : std::runtime_error(message) {}
	};

	template <typename T>
	T get(const std::string& key) {
		return std::get<T>(data[key]);
	}

	int count(const std::string& key) const {
		return data.count(key);
	}
};

#endif