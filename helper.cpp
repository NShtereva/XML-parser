#include "helper.hpp"

#include <cstring>

unsigned int Helper::numberOfDigits(unsigned int num)
{
    unsigned int counter = 0;
    while(num != 0)
    {
        num = num / 10;
        counter++;
    }
    return counter;
}

char* Helper::toString(unsigned int num)
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

unsigned int Helper::toNumber(const char* str)
{
    unsigned int result = 0;

    int len = strlen(str);
    for(int i = 0; i < len; i++)
    {
        result = result * 10 + (str[i] - '0');
    }

    return result;
}

void Helper::processTheIndentation(std::ostream& out, unsigned int level)
{
    while(level > 0)
    {
        out << "\t";
        level--;
    }
}

void Helper::inLowerCase(char*& str)
{
    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = 'a' + (str[i] - 'A');
    }
}

bool Helper::isValidFileName(const char* fileName, const size_t MAX_LEN)
{
    int len = strlen(fileName);

    return fileName[len - 4] == '.' && fileName[len - 3] == 'x' &&
           fileName[len - 2] == 'm' && fileName[len - 1] == 'l';
}
