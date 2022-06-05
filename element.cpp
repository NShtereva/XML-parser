#include "element.hpp"

#include <cstring>

#include "elementHelper.hpp"

unsigned int Element::counter = 1;

Element::Element() 
    : label(nullptr), level(0), text(nullptr)
{
    this->setId();
}

Element::Element(const Element& other) 
    : label(nullptr), level(0), text(nullptr)
{
    this->setId();
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
        throw MyException("Invalid label!");

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
    char* idValue = ElementHelper::toString(this->counter);

    this->id.setLabel("id");
    this->id.setValue(idValue);
    
    delete[] idValue;
    idValue = nullptr;

    this->counter++;
}

void Element::setText(const char* text)
{
    if(!text || strlen(text) >= MAX_LEN) 
        throw MyException("Invalid text!");

    delete[] this->text;

    this->text = new(std::nothrow) char[strlen(text) + 1];
    if(!this->text)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->text, text);
}

std::ostream& operator << (std::ostream& out, const Element& element)
{
    ElementHelper::getInstance().processTheIndentation(out, element.level);
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

        ElementHelper::getInstance().processTheIndentation(out, element.level);
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

    if(c == ' ')
    {
        while(c != '>')
        {
            Attribute a;
            in >> a;

            if(strcmp(a.getLabel(), "id") == 0)
                element.id.setValue(a.getValue());
            else
                element.attributes.add(a);

            in.get(c);
        }
    }

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

    in.get(); // '\n'

    return in;
}
