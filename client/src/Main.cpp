#include <iostream>
#include <string>

#include "StringHandler.h"

int main()
{
    std::string input;
    std::cin >> input;

    try
    {
        StringHandler handler(input);
        std::cout << handler.GetKBString();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return EXIT_SUCCESS;
}