#ifndef __MYEXCEPTION_HPP
#define __MYEXCEPTION_HPP

#include <exception>

class MyException : public std::exception
{
    private:
        char* message;

        void setMessage(const char* message);

    public:
        MyException(const char* message);
        MyException(const MyException& other);
        ~MyException();

        MyException& operator = (const MyException& other);

        const char* what() const noexcept override final;
};

#endif
