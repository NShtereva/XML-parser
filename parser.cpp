#include "parser.hpp"

#include "commandParser.hpp"
#include "commandExecutor.hpp"

void Parser::useParser()
{
    char line[MAX_LEN];

    while(true)
    {
        std::cout << "> ";
        std::cin.getline(line, MAX_LEN);

        CommandParser parser(line);
        CommandExecutor::getInstance().execute(parser);
    }
}
