#include "attribute.hpp"

#include <cstring>
#include <cassert>
#include <exception>

Attribute::Attribute() : key(nullptr), value(nullptr)
{ }

Attribute::Attribute(const char* key, const char* value)
    : key(nullptr), value(nullptr)
{
    try
    {
        this->setKey(key);
        this->setValue(value);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }    
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
        try
        {
            this->setKey(other.key);
            this->setValue(other.value);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
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
        throw std::invalid_argument("Invalid key!");
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
        throw std::invalid_argument("Invalid value!");
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

    try
    {
        in.getline(buffer, attribute.MAX_LEN, '=');
        attribute.setKey(buffer);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }

    in.get(); // '\"'

    try
    {
        in.getline(buffer, attribute.MAX_LEN, '\"');
        attribute.setValue(buffer);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }

    return in;
}
