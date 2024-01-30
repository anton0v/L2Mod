#include "Summator.h"

#include <stdexcept>

Summator::Summator(std::string input) :
    _sum(0)
{
    SumFromKBString(input);
}

void Summator::SumFromKBString(std::string input)
{
    _sum = 0;
    if(input.find_first_not_of("0123456789KB") != std::string::npos)
        throw std::runtime_error("string must contain only digits and KB");
    
    for(int i = 0; i < input.size(); ++i)
    {
        if(input[i] != 'K' && input[i] != 'B')
            _sum += input[i] - 48;
    }
}
