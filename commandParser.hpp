#ifndef __COMMANDPARSER_HPP
#define __COMMANDPARSER_HPP

#include <iostream>

class CommandParser
{
	private:
		static const size_t MAX_NUMBER_OF_ARGS = 10; 
		static const size_t MAX_LEN = 255; 

		char** arguments;
		size_t numberOfArgs;

		void allocate();
		void deallocate();

		void processTheLine(const char* line);

	public:
		CommandParser(const char* line);
        CommandParser(const CommandParser& other);
        ~CommandParser();

    	CommandParser& operator = (const CommandParser& other);

		size_t getNumberOfArguments() const;

		const char* operator [] (int index) const;
};

#endif
