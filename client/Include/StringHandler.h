#ifndef STRINGHANDLER_H

#define SYMBOL_LIMIT 64

#include <string>

class StringHandler
{
private:
    std::string _KBString;
public:
    StringHandler(std::string input = "");
    bool Handle(std::string input);
    const std::string& GetKBString() const {return _KBString;}
    int GetSymbolLimit() const {return SYMBOL_LIMIT;}
};

#endif