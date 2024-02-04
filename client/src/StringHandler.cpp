#include "StringHandler.h"

#include <regex>
#include <algorithm>
#include <stdexcept>

StringHandler::StringHandler(std::string input)
{
    Handle(input);
}

bool StringHandler::Handle(std::string input)
{
    if( input.size() > SYMBOL_LIMIT 
        || input.find_first_not_of("0123456789") != std::string::npos) 
        return false;

    std::sort(input.begin(), input.end(), std::greater<char>());
    
    _KBString = std::regex_replace(input, std::regex("[02468]"), "KB");

    return true;
}
