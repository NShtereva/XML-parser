#ifndef __ELEMENTHELPER_HPP
#define __ELEMENTHELPER_HPP

#include <iostream>

class ElementHelper
{
    private:
        ElementHelper() = default;

    public:
        ElementHelper(const ElementHelper& other) = delete;
        ElementHelper& operator = (const ElementHelper& other) = delete;

        static ElementHelper& getInstance();

        static unsigned int numberOfDigits(unsigned int num);
        static char* toString(unsigned int num);
        static void processTheIndentation(std::ostream& out, unsigned int level);
};

#endif
