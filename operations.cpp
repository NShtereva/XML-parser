#include "operations.hpp"

Operations::Operations(const Element& element) 
    : element(element)
{ }

void Operations::print() const
{
    std::cout << this->element;
}

void Operations::select(const char* id, const char* key) const
{
    if(!this->element.getAttributeValue(id, key))
    {
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
        return;
    }

    std::cout << this->element.getAttributeValue(id, key) << std::endl;
}

void Operations::set(const char* id, const char* key, const char* value)
{
    bool flag = this->element.setAttributeValue(id, key, value);
    
    if(!flag) 
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
}

Array<Attribute> Operations::children(const char* id) const
{
    return this->element.getChildrenAttributes(id);
}

void Operations::deleteAttribute(const char* id, const char* key)
{
    bool flag = this->element.deleteAttribute(id, key);
    
    if(!flag) 
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
}

void Operations::newchild(const char* id)
{
    bool flag = this->element.addNestedElement(id);
    
    if(!flag) 
        std::cout << "There is no element with this id!" << std::endl;
}
