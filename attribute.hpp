#ifndef __ATTRIBUTE_HPP
#define __ATTRIBUTE_HPP

#include <iostream>

class Attribute
{
    private:
        static const size_t MAX_LEN = 255;
        char* key;
        char* value;

    public:
        Attribute();
        Attribute(const char* key, const char* value);
        Attribute(const Attribute& other);
        ~Attribute();

        Attribute& operator = (const Attribute& other);

        const char* getKey() const;
        const char* getValue() const;

        void setKey(const char* key);
        void setValue(const char* value);

        friend std::ostream& operator << (std::ostream& out, const Attribute& attribute);
        friend std::istream& operator >> (std::istream& in, Attribute& attribute);
};

#endif
