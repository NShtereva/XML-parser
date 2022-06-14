#include "element.hpp"

#include <cstring>
#include <exception>

#include "helper.hpp"
#include "myException.hpp"

unsigned int Element::nextId = 1;

Element::Element() 
    : label(nullptr), level(0), text(nullptr)
{
    this->setId();
}

Element::Element(const Element& other) 
    : label(nullptr), level(0), text(nullptr)
{
    this->copy(other);
}

Element::~Element()
{
    this->deallocate();
}

Element& Element::operator = (const Element& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }
    return *this;
}

void Element::copy(const Element& other)
{
    this->id = other.id;

    if(other.label) 
        this->setLabel(other.label);

    this->attributes = other.attributes;
    this->nestedElements = other.nestedElements;

    this->level = other.level;
        
    if(other.text) 
        this->setText(other.text);
}

void Element::deallocate()
{
    delete[] this->label;
    this->label = nullptr;

    delete[] this->text;
    this->text = nullptr;
}

void Element::setLabel(const char* label)
{
    if(!label || strlen(label) >= MAX_LEN) 
        throw std::invalid_argument("Invalid label!");

    delete[] this->label;

    this->label = new(std::nothrow) char[strlen(label) + 1];
    if(!this->label)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->label, label);
}

void Element::setId()
{
    char* idValue = Helper::toString(nextId);

    this->id.setKey("id");
    this->id.setValue(idValue);
    
    delete[] idValue;
    idValue = nullptr;

    nextId++;
}

void Element::addSuffix(const char* suffix)
{
    char* currStr = new(std::nothrow) char[strlen(this->id.getValue()) + strlen(suffix) + 1];
    if(!currStr)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(currStr, this->id.getValue());
    this->id.setValue(strcat(currStr, suffix));
    
    delete[] currStr;
    currStr = nullptr;
}

void Element::processDuplicateIds()
{
    int size = this->nestedElements.getSize();
    for(int i = 0; i < size; i++)
    {
        if(strcmp(this->id.getValue(), this->nestedElements[i].id.getValue()) == 0)
        {
            this->addSuffix("_1");
            this->nestedElements[i].addSuffix("_2");
        } 
    }
}

void Element::setText(const char* text)
{
    if(!text || strlen(text) >= MAX_LEN) 
        throw std::invalid_argument("Invalid text!");

    delete[] this->text;

    this->text = new(std::nothrow) char[strlen(text) + 1];
    if(!this->text)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->text, text);
}

int Element::functionHelper(const Element* element, const char* id, const char* key) const
{
    int index = -1;

    if(strcmp(element->id.getValue(), id) == 0)
    {
        int numberOfAttributes = element->attributes.getSize();

        for(int i = 0; i < numberOfAttributes && index == -1; i++)
        {
            if(strcmp(element->attributes[i].getKey(), key) == 0)
                index = i;
        }
    }

    return index;
}

const char* Element::getAttributeValue(const char* id, const char* key) const
{
    int index = this->functionHelper(this, id, key);

    if(index != -1)
         return this->attributes[index].getValue();       

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].getAttributeValue(id, key))
            return this->nestedElements[i].getAttributeValue(id, key);
    }

    return nullptr;
}

bool Element::setAttributeValue(const char* id, const char* key, const char* value)
{
    int index = this->functionHelper(this, id, key);

    if(index != -1)
    {
        this->attributes[index].setValue(value);
        return true;
    }

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].setAttributeValue(id, key, value))
            return true;
    }

    return false;
}

bool Element::deleteAttribute(const char* id, const char* key)
{
    int index = this->functionHelper(this, id, key);

    if(index != -1)
    {
        this->attributes.deleteAt(index);
        return true;
    }

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].deleteAttribute(id, key))
            return true;
    }

    return false;
}

bool Element::addNestedElement(const char* id)
{
    if(strcmp(this->id.getValue(), id) == 0)
    {
        Element e;
        e.level = this->level + 1;
        e.setLabel("<unknown>");
        e.setText("<unknown>");

        this->nestedElements.add(e);
        return true;
    }

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].addNestedElement(id))
            return true;
    }

    return false;
}

bool Element::getChildrenAttributesHelper(const Element* element, const char* id, Array<Attribute>& array) const
{
    if(strcmp(element->id.getValue(), id) == 0)
    {
        int numberOfNestedElements = element->nestedElements.getSize();

        for(int i = 0; i < numberOfNestedElements; i++)
        {
            int numberOfAttributes = element->nestedElements[i].attributes.getSize();

            for(int j = 0; j < numberOfAttributes; j++)
            {
                array.add(element->nestedElements[i].attributes[j]);
            }
        }

        return true;
    }

    return false;
}

Array<Attribute> Element::getChildrenAttributes(const char* id) const
{
    Array<Attribute> array;

    bool flag = this->getChildrenAttributesHelper(this, id, array);
    if(flag) return array;

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        flag = this->getChildrenAttributesHelper(&this->nestedElements[i], id, array);
        if(flag) return array;
    }

    return array;
}

bool Element::getChildHelper(unsigned int n, Element& child) const
{
    if(this->level == n)
    {
        child = *this;
        return true;
    }

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].getChildHelper(n, child))
            return true;
    }

    return false;
}

const Element Element::getChild(const char* id, unsigned int n, bool& isFound) const
{
    if(strcmp(this->id.getValue(), id) == 0)
    {
        int numberOfNestedElements = this->nestedElements.getSize();

        Element child;
        child.setLabel("<unknown>");
        child.setText("<unknown>");

        int N = n + this->level;

        for(int i = 0; i < numberOfNestedElements && !isFound; i++)
        {
            isFound = this->nestedElements[i].getChildHelper(N, child);
        }

        child.level = 0;
        return child;
    }

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        Element child = this->nestedElements[i].getChild(id, n, isFound);
        if(isFound) return child;
    }

    Element child;
    child.setLabel("<unknown>");
    child.setText("<unknown>");

    return child;
}

const char* Element::getText(const char* id) const
{
    if(strcmp(this->id.getValue(), id) == 0)
        return this->text;

    int numberOfNestedElements = this->nestedElements.getSize();

    for(int i = 0; i < numberOfNestedElements; i++)
    {
        if(this->nestedElements[i].getText(id))
            return this->nestedElements[i].getText(id);
    }

    return nullptr;
}

std::ostream& operator << (std::ostream& out, const Element& element)
{
    Helper::processTheIndentation(out, element.level);
    out << "<" << element.label << " " << element.id;

    int attribSize = element.attributes.getSize();
    
    if(attribSize > 0)
    {
        for(int i = 0; i < attribSize; i++)
        {
            out << " " << element.attributes[i];
        }
    }

    out << ">";

    int size = element.nestedElements.getSize();

    if(size > 0)
    {
        // nested elements
        out << std::endl;

        for(int i = 0; i < size; i++)
        {
            out << element.nestedElements[i];
        }

        Helper::processTheIndentation(out, element.level);
    }
    else
    {
        // text
        out << element.text;
    }
    
    out << "</" << element.label << ">" << std::endl;

    return out;
}

std::istream& operator >> (std::istream& in, Element& element)
{
    char buffer[element.MAX_TEXT_LEN];
    buffer[0] = '\0';

    if(element.level == 0) 
        in.getline(buffer, element.MAX_TEXT_LEN, '<'); // '\t'

    char c; in.get(c);
    int i = 0;

    while(c != ' ' && c != '>')
    {
        buffer[i] = c;
        i++;
        in.get(c);
    }
    buffer[i] = '\0';

    element.setLabel(buffer);

    char saveId[element.MAX_LEN];
    saveId[0] = '\0';

    if(c == ' ')
    {
        while(c != '>')
        {
            Attribute a;
            in >> a;

            if(strcmp(a.getKey(), "id") == 0)
                strcpy(saveId, a.getValue());
            else
                element.attributes.add(a);

            in.get(c);
        }
    }

    if(strlen(saveId) > 0) 
        element.id.setValue(saveId);

    in.get(c);

    if(c != '\n')
    {
        // text
        in.putback(c);

        in.getline(buffer, element.MAX_TEXT_LEN, '<');
        element.setText(buffer);
    }
    else
    {
        // nested elements
        in.getline(buffer, element.MAX_LEN, '<');

        int currOffset = element.level * 4 + 4;
        while(strlen(buffer) == currOffset)
        {
            Element el;
            el.level = (currOffset - 4) / 4 + 1;
            in >> el;

            element.nestedElements.add(el);
            in.getline(buffer, element.MAX_LEN, '<');
        }

        if(strlen(buffer) != currOffset - 4)
            throw MyException("Invalid indentation!");
    }

    in.get(); // '/'

    in.getline(buffer, element.MAX_LEN, '>');
    if(strcmp(element.label, buffer) != 0)
        throw MyException("Invalid element!");

    element.processDuplicateIds();

    in.get(); // '\n'

    return in;
}
