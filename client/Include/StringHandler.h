#ifndef STRINGHANDLER_H

#define SYMBOL_LIMIT 64

#include <string>
#include <regex>

class StringHandler
{
private:
    std::string KBString;
public:
    StringHandler(std::string input = "");
    void Handle(std::string input);
    const std::string& GetKBString() const {return KBString;}
    int GetSymbolLimit() const {return SYMBOL_LIMIT;}
};

#endif