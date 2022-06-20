#include "parser.hpp"

#include "commandParser.hpp"
#include "commandExecutor.hpp"

void Parser::useParser()
{
    char line[MAX_LEN];
    bool calledExit = false;

    while(!calledExit)
    {
        std::cout << "> ";
        std::cin.getline(line, MAX_LEN);

        CommandParser parser(line);
        calledExit = CommandExecutor::getInstance().execute(parser);
    }
}
