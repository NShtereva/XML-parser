#include "attribute.hpp"

#include <cstring>
#include <cassert>

#include "myException.hpp"

Attribute::Attribute() : label(nullptr), value(nullptr)
{ }

Attribute::Attribute(const char* label, const char* value)
    : label(nullptr), value(nullptr)
{
    this->setLabel(label);
    this->setValue(value);
}

Attribute::Attribute(const Attribute& other)
    : Attribute(other.label, other.value)
{ }

Attribute::~Attribute()
{
    delete[] this->label;
    this->label = nullptr;

    delete[] this->value;
    this->value = nullptr;
}

Attribute& Attribute::operator = (const Attribute& other)
{
    if(this != &other)
    {
        this->setLabel(other.label);
        this->setValue(other.value);
    }
    return *this;
}

void Attribute::setLabel(const char* label)
{
    if(!label || strlen(label) > this->MAX_LEN)
    {
        throw MyException("Invalid label!");
    }

    delete[] this->label;

    this->label = new(std::nothrow) char[strlen(label) + 1];
    if(!this->label)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->label, label);
}

void Attribute::setValue(const char* value)
{
    if(!value || strlen(value) > this->MAX_LEN)
    {
        throw MyException("Invalid value!");
    }

    delete[] this->value;

    this->value = new(std::nothrow) char[strlen(value) + 1];
    if(!this->value)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->value, value);
}

const char* Attribute::getLabel() const
{
    return this->label;
}

const char* Attribute::getValue() const
{
    return this->value;
}

std::ostream& operator << (std::ostream& out, const Attribute& attribute)
{
    out << attribute.label << "=\"" << attribute.value << "\"";
    return out;
}

std::istream& operator >> (std::istream& in, Attribute& attribute)
{
    char buffer[attribute.MAX_LEN];

    in.getline(buffer, attribute.MAX_LEN, '=');
    attribute.setLabel(buffer);

    in.get(); // '='
    in.get(); // '\"'

    in.getline(buffer, attribute.MAX_LEN, '\"');
    attribute.setValue(buffer);

    in.get(); // '\"'

    return in;
}
