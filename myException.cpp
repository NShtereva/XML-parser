#include "myException.hpp"

#include <iostream>
#include <cstring>

MyException::MyException(const char* message)
    : message(nullptr)
{
    this->setMessage(message);
}

MyException::MyException(const MyException& other)
    : message(nullptr)
{
    this->setMessage(other.message);
}

MyException::~MyException()
{
    delete[] this->message;
    this->message = nullptr;
}

MyException& MyException::operator = (const MyException& other)
{
    if(this != &other)
    {
        this->setMessage(other.message);
    }
    return *this;
}

void MyException::setMessage(const char* message)
{
    delete[] this->message;

    this->message = new(std::nothrow) char[strlen(message) + 1];
    if(!this->message)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(this->message, message);
}

const char* MyException::what() const noexcept
{
    return this->message;
}
