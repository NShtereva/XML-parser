#ifndef __ARRAY_HPP
#define __ARRAY_HPP

#include <iostream>
#include <cassert>

#include "myException.hpp"

template <typename T>
class Array
{
    private:
        static const size_t INITIAL_CAPACITY = 2;
        static const size_t INCREASE_STEP = 2;

        T** elements;
        size_t size;
        size_t capacity;

        void allocate(const size_t size);
        void copy(const Array& other);
        void deallocate();
        
        void resize();
        
    public:
        Array();
        Array(const Array& other);
        ~Array();

        Array& operator = (const Array& other);

        size_t getSize() const;

        void add(const T& element);

        void deleteAt(int index);

        T& operator [] (int index);
        const T& operator [] (int index) const;

        template <typename U>
        friend std::ostream& operator << (std::ostream& out, const Array<U>& array);
};

template <typename T>
Array<T>::Array()
{
    this->allocate(INITIAL_CAPACITY);
    this->size = 0;
    this->capacity = INITIAL_CAPACITY;
}

template <typename T>
Array<T>::Array(const Array& other)
{
    this->copy(other);
}

template <typename T>
Array<T>::~Array()
{
    this->deallocate();
}

template <typename T>
Array<T>& Array<T>::operator = (const Array& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }

    return *this;
}

template <typename T>
void Array<T>::allocate(const size_t size)
{
    if(size < INITIAL_CAPACITY)
        throw MyException("Invalid size!");

    this->elements = new(std::nothrow) T*[size];
    if(!this->elements)
    {
        std::cout << "Memory not allocated successfully!\n";
        return;
    }
}

template <typename T>
void Array<T>::copy(const Array& other)
{
    this->allocate(other.capacity);

    for(int i = 0; i < other.size; i++)
    {
        this->elements[i] = new(std::nothrow) T(*other.elements[i]);
        if(!this->elements[i])
        {
            std::cout << "Memory not allocated successfully!\n";
            return;
        }
    }

    this->size = other.size;
    this->capacity = other.capacity;
}

template <typename T>
void Array<T>::deallocate()
{
    for(int i = 0; i < this->size; i++)
    {
        delete this->elements[i];
    }
    delete[] this->elements;
    this->elements = nullptr;
}

template <typename T>
void Array<T>::resize()
{
    T** newArr = new(std::nothrow) T*[this->capacity * INCREASE_STEP];
    if(!newArr)
    {
        std::cout << "Memory not allocated successfully!\n";
        return;
    }

    for(int i = 0; i < this->size; i++)
    {
        newArr[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newArr;
    newArr = nullptr;

    this->capacity *= INCREASE_STEP;
}

template <typename T>
size_t Array<T>::getSize() const
{
    return this->size;
}

template <typename T>
void Array<T>::add(const T& element)
{
    if(this->size + 1 > this->capacity)
    {
        resize();
    }

    this->elements[this->size] = new(std::nothrow) T(element);
    if(!this->elements[this->size])
    {
        std::cout << "Memory not allocated successfully!\n";
        return;
    }

    this->size++;
}

template <typename T>
void Array<T>::deleteAt(int index)
{
    if(index < 0 && index > this->size - 1)
        throw MyException("Invalid index!");

    if(index == size - 1)
    {
        delete this->elements[size - 1];
        this->size--;
        return;
    }
    
    T* save = this->elements[index];
    
    for(int i = index; i < this->size - 1; i++)
    {
        this->elements[i] = this->elements[i + 1];
    }

    delete save;
    this->size--;
}

template <typename T>
T& Array<T>::operator [] (int index)
{
    if(index < 0 && index > this->size - 1)
        throw MyException("Invalid index!");
    return *this->elements[index];
}

template <typename T>
const T& Array<T>::operator [] (int index) const
{
    if(index < 0 && index > this->size - 1)
        throw MyException("Invalid index!");
    return *this->elements[index];
}

template <typename U>
std::ostream& operator << (std::ostream& out, const Array<U>& array)
{
    int size = array.getSize();
    for(int i = 0; i < size; i++)
    {
        out << array[i] << std::endl;
    }
    return out;
}

#endif
