#include "StringHandler.h"

#include <regex>
#include <algorithm>

StringHandler::StringHandler(std::string input)
{
    Handle(input);
}

void StringHandler::Handle(std::string input)
{
    if(input.size() > SYMBOL_LIMIT)
        throw std::runtime_error("string max size is 64");
    
    if(input.find_first_not_of("0123456789") != std::string::npos)
        throw std::runtime_error("string must contain only digits");

    std::sort(input.begin(), input.end(), std::greater<char>());
    
    KBString = std::regex_replace(input, std::regex("[02468]"), "KB");
}
