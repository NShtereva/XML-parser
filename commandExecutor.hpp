#ifndef _COMMANDEXECUTOR_HPP
#define _COMMANDEXECUTOR_HPP

#include <iostream>
#include <fstream>

#include "element.hpp"
#include "commandParser.hpp"

class CommandExecutor
{
	private:
	    static const size_t MAX_LEN = 255;

	    Element element;
	    char fileName[MAX_LEN];
	    bool isSaved, isFirstCommand;

	    CommandExecutor();

	    void open(const char* fileName);
	    void close();
	    void save();
	    void saveAs(const char* fileName);
	    static void help();
	    void exit(const CommandParser& parser);

	    void print() const;
            void select(const char* id, const char* key) const;
            void set(const char* id, const char* key, const char* value);
            void children(const char* id) const;
            void child(const char* id, unsigned int n) const;
            void text(const char* id) const;
            void deleteAttribute(const char* id, const char* key);
            void newchild(const char* id);
		
	    bool isValidCommand(const CommandParser& parser) const;

	public:
	    CommandExecutor(const CommandExecutor& other) = delete;
            CommandExecutor& operator = (const CommandExecutor& other) = delete;

            static CommandExecutor& getInstance();

	    bool execute(const CommandParser& parser);
};

#endif
