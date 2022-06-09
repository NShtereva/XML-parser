#ifndef __OPERATIONS_HPP
#define __OPERATIONS_HPP

#include "element.hpp"

class Operations
{
    private:
        Element element;

    public:
        Operations(const Element& element);

        void print() const;
        void select(const char* id, const char* key) const;
        void set(const char* id, const char* key, const char* value);
        Array<Attribute> children(const char* id) const;
        void deleteAttribute(const char* id, const char* key);
        void newchild(const char* id);
};

#endif
