#include "attribute.hpp"

#include <cstring>
#include <cassert>

#include "myException.hpp"

Attribute::Attribute() : key(nullptr), value(nullptr)
{ }

Attribute::Attribute(const char* key, const char* value)
    : key(nullptr), value(nullptr)
{
    this->setKey(key);
    this->setValue(value);
}

Attribute::Attribute(const Attribute& other)
    : Attribute(other.key, other.value)
{ }

Attribute::~Attribute()
{
    delete[] this->key;
    this->key = nullptr;

    delete[] this->value;
    this->value = nullptr;
}

Attribute& Attribute::operator = (const Attribute& other)
{
    if(this != &other)
    {
        this->setKey(other.key);
        this->setValue(other.value);
    }
    return *this;
}

const char* Attribute::getKey() const
{
    return this->key;
}

const char* Attribute::getValue() const
{
    return this->value;
}

void Attribute::setKey(const char* key)
{
    if(!key || strlen(key) > this->MAX_LEN)
    {
        throw MyException("Invalid key!");
    }

    delete[] this->key;

    this->key = new(std::nothrow) char[strlen(key) + 1];
    if(!this->key)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->key, key);
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

std::ostream& operator << (std::ostream& out, const Attribute& attribute)
{
    out << attribute.key << "=\"" << attribute.value << "\"";
    return out;
}

std::istream& operator >> (std::istream& in, Attribute& attribute)
{
    char buffer[attribute.MAX_LEN];

    in.getline(buffer, attribute.MAX_LEN, '=');
    attribute.setKey(buffer);

    in.get(); // '\"'

    in.getline(buffer, attribute.MAX_LEN, '\"');
    attribute.setValue(buffer);

    return in;
}
