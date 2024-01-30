#include <iostream>
#include <string>

#include "StringHandler.h"
#include "Summator.h"

int main()
{
    std::string input;
    std::cin >> input;

    try
    {
        StringHandler handler(input);
        std::string res = handler.GetKBString();

        Summator summator(res);

        std::cout << res << "\n";
        std::cout << summator.GetSum();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return EXIT_SUCCESS;
}