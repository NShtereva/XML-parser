#ifndef __ELEMENT_HPP
#define __ELEMENT_HPP

#include "array.hpp"
#include "attribute.hpp"

class Element
{
    private:
        static const size_t MAX_LEN = 255;
        static const size_t MAX_TEXT_LEN = 1000;
        static unsigned int counter;

        char* label;
        Attribute id;
        Array<Attribute> attributes;
        Array<Element> nestedElements;
        unsigned int level;
        char* text;

        void copy(const Element& other);
        void deallocate();

        void setLabel(const char* label);
        void setId();
        void setText(const char* text);
        
    public:
        Element();
        Element(const Element& other);
        ~Element();

        Element& operator = (const Element& other);

        friend std::ostream& operator << (std::ostream& out, const Element& element);
        friend std::istream& operator >> (std::istream& in, Element& element);
};

#endif
