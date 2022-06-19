#include "commandParser.hpp"

#include <fstream>
#include <cstring>
#include <exception>

#include "helper.hpp"

CommandParser::CommandParser(const char* line)
    : numberOfArgs(0)
{
    try
    {
        this->allocate();
        this->processTheLine(line);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}

CommandParser::CommandParser(const CommandParser& other)
{
    this->allocate();
    for(int i = 0; i < other.numberOfArgs; i++)
    {
        strcpy(this->arguments[i], other.arguments[i]);
    }
    this->numberOfArgs = other.numberOfArgs;
}

CommandParser::~CommandParser()
{
    this->deallocate();
}

CommandParser& CommandParser::operator = (const CommandParser& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->allocate();

        for(int i = 0; i < other.numberOfArgs; i++)
        {
            strcpy(this->arguments[i], other.arguments[i]);
        }

        this->numberOfArgs = other.numberOfArgs;
    }
    return *this;
}

void CommandParser::allocate()
{
    this->arguments = new(std::nothrow) char*[this->MAX_NUMBER_OF_ARGS];
    if(!this->arguments)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    for(int i = 0; i < this->MAX_NUMBER_OF_ARGS; i++)
    {
        this->arguments[i] = new(std::nothrow) char[this->MAX_LEN];
        if(!this->arguments[i])
        {
            std::cout << "Memory not allocated successfully!" << std::endl;

            delete[] this->arguments;
            this->arguments = nullptr;

            return;
        }
    }
}

void CommandParser::deallocate()
{
    for(int i = 0; i < this->MAX_NUMBER_OF_ARGS; i++)
    {
        delete[] this->arguments[i];
    }
    delete[] this->arguments;
    this->arguments = nullptr;
}

void CommandParser::processTheLine(const char* line)
{
    int lineSize = strlen(line);

    int i = 0, index = 0;
    while(i < lineSize && index <= this->MAX_NUMBER_OF_ARGS)
    {
        this->arguments[index][0] = '\0';

        while(Helper::isWhiteSpace(line[i]) && i < lineSize)
        {
            i++;
        }

        if(line[i] == '\"')
        {
            i++;

            int j = 0;
            while(line[i] != '\"' && i < lineSize)
            {
                this->arguments[index][j] = line[i];
                i++; j++;
            }
            this->arguments[index][j] = '\0';

            if(line[i] != '\"')
                throw std::invalid_argument("Invalid input!");
            else i++;

            index++;
            continue;
        }

        int j = 0;
        while(!Helper::isWhiteSpace(line[i]) && i < lineSize)
        {
            this->arguments[index][j] = line[i];
            i++; j++;
        }
        
        if(j > 0)
        {
            this->arguments[index][j] = '\0';
            index++;
        }
    }

    if(index > this->MAX_NUMBER_OF_ARGS)
        throw std::invalid_argument("Invalid input!");

    this->numberOfArgs = index;
}

size_t CommandParser::getNumberOfArguments() const
{
    return this->numberOfArgs;
}

const char* CommandParser::operator [] (int index) const
{
    if(index < 0 || index > this->MAX_NUMBER_OF_ARGS)
        throw std::out_of_range("Invalid index!");

    return this->arguments[index];
}
