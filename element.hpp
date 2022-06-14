#ifndef __ELEMENT_HPP
#define __ELEMENT_HPP

#include "array.hpp"
#include "attribute.hpp"

class Element
{
    private:
        static const size_t MAX_LEN = 255;
        static const size_t MAX_TEXT_LEN = 1000;

        static unsigned int nextId;

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
        void addSuffix(const char* suffix);
        void processDuplicateIds();

        void setText(const char* text);

        int functionHelper(const Element* element, const char* id, const char* key) const;
        
        bool getChildrenAttributesHelper(const Element* element, const char* id, 
                                                           Array<Attribute>& array) const;

        bool getChildHelper(unsigned int n, Element& child) const;

    public:
        Element();
        Element(const Element& other);
        ~Element();

        Element& operator = (const Element& other);

        const char* getAttributeValue(const char* id, const char* key) const;
        
        bool setAttributeValue(const char* id, const char* key, const char* value);

        bool deleteAttribute(const char* id, const char* key);

        bool addNestedElement(const char* id);

        Array<Attribute> getChildrenAttributes(const char* id) const;

        // n > 0
        const Element getChild(const char* id, unsigned int n, bool& isFound) const;

        const char* getText(const char* id) const;

        friend std::ostream& operator << (std::ostream& out, const Element& element);
        friend std::istream& operator >> (std::istream& in, Element& element);
};

#endif
