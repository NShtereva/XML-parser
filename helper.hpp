#ifndef __HELPER_HPP
#define __HELPER_HPP

#include <iostream>

class Helper
{
    private:
        Helper() = default;

    public:
        static unsigned int numberOfDigits(unsigned int num);

        static char* toString(unsigned int num);
        static unsigned int toNumber(const char* str);

        static void processTheIndentation(std::ostream& out, unsigned int level);

        static void inLowerCase(char*& str);

	static bool isValidFileName(const char* fileName);

        static bool isWhiteSpace(char a);
};

#endif
