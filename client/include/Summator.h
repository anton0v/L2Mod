#ifndef SUMMATOR_H

#include <string>

class Summator
{
private:
    int _sum;
public:
    Summator(std::string input = "");
    void SumFromKBString(std::string input);
    int GetSum() const {return _sum;}
};

#endif