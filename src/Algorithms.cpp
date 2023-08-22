#include "Algorithms.h"

#include <regex>

std::string doubleToString(const double value)
{
    std::string result = std::to_string(value);

    const std::regex integerRegex("^([0-9]+?)(?:\\.0+)$");
    const std::regex trailingSpacesRegex("^([0-9]+?\\.[0-9]*?[1-9])0*$");

    std::smatch match;

    if (std::regex_match(result, match, integerRegex)
        || std::regex_match(result, match, trailingSpacesRegex))
    {
        result = match[1];
    }

    return result;
}
