#include "elementHelper.hpp"

#include <cstring>

ElementHelper& ElementHelper::getInstance()
{
    static ElementHelper object;
    return object;
}

unsigned int ElementHelper::numberOfDigits(unsigned int num)
{
    unsigned int counter = 0;
    while(num != 0)
    {
        num = num / 10;
        counter++;
    }
    return counter;
}

char* ElementHelper::toString(unsigned int num)
{
    unsigned int size = numberOfDigits(num);

    char* result = new(std::nothrow) char[size + 1];
    if(!result)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return nullptr;
    }

    for(int i = size - 1; i >= 0; i--)
    {
        result[i] = (num % 10) + '0';
        num = num / 10;
    }
    result[size] = '\0';

    return result;
}

void ElementHelper::processTheIndentation(std::ostream& out, unsigned int level)
{
    while(level > 0)
    {
        out << "\t";
        level--;
    }
}
