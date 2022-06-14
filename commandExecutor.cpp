#include "commandExecutor.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

#include "helper.hpp"

CommandExecutor::CommandExecutor() 
    : isSaved(true), isFirstCommand(true)
{ }

CommandExecutor& CommandExecutor::getInstance()
{
    static CommandExecutor object;
    return object;
}

void CommandExecutor::open(const char* fileName)
{
    if(strlen(fileName) >= this->MAX_LEN)
    {
        std::cout << "Invalid file name!" << std::endl;
        return;
    }

    std::ifstream iFile(fileName);
    if(iFile.is_open())
    {
        std::cout << "Successfully opened " << fileName << std::endl;
        strcpy(this->fileName, fileName);
        this->isFirstCommand = false;

        iFile >> this->element;

        iFile.close();
    }
    else
    {
        std::ofstream oFile(fileName);
        if (!oFile)
        {    
            std::cout << "Problem while opening " << fileName << std::endl;
            return;
        }
        
        std::cout << "Successfully opened " << fileName << std::endl;
        strcpy(this->fileName, fileName);
        oFile.close();
    }
}

void CommandExecutor::close()
{
    this->element = Element();
    std::cout << "Successfully closed " << this->fileName << std::endl;
    this->isSaved = true;
    this->isFirstCommand = true;
}

void CommandExecutor::save()
{ 
    std::ofstream file(this->fileName);
    if (!file)
    {    
        std::cout << "File problem!" << std::endl;
        return;
    }

    file << this->element;
    file.close();

    std::cout << "Successfully saved " << fileName << std::endl;
    this->isSaved = true;
}

void CommandExecutor::saveAs(const char* fileName)
{
    std::ofstream newFile(fileName);
    if(!newFile)
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return;
    }

    newFile << this->element;
    std::cout << "Successfully saved " << fileName << std::endl;
    this->isSaved = true;

    newFile.close();
}

void CommandExecutor::help()
{
    std::cout << "The following commands are supported:\n"
              << "open <file>\t\topens <file>\n"
              << "close\t\t\tcloses currently opened file\n"
              << "save\t\t\tsaves the currently open file\n"
              << "save as <file>\t\tsaves the currently open file in <file>\n"
              << "help\t\t\tprints this information \n"
              << "exit\t\t\texists the program\n"
              << "print\t\t\tdisplays the information read from an XML file\n"
              << "select <id> <key>\tdisplays the value of an attribute by an element id and the attribute key\n"
              << "set <id> <key> <value>\tassign an attribute value\n"
              << "children <id>\t\tlist of attributes of nested element\n"
              << "child <id> <n>\t\taccess to the nth successor of an element\n"
              << "text <id>\t\taccess to element text\n"
              << "delete <id> <key>\tdelete an element attribute\n"
              << "newchild <id>\t\tadds a new successor to an element\n\n"
              << "If you select the command save as, it must be enclosed in double quotes -> \"save as\"\n"
              << std::endl;
}

void CommandExecutor::exit(const CommandParser& parser)
{
    if(strcmp(parser[0], "close") == 0)
    {
        this->close();
    }
    else if(strcmp(parser[0], "save") == 0)
    {
        this->save();
    }
    else if(strcmp(parser[0], "save as") == 0)
    {
        this->saveAs(parser[1]);
    }
}

void CommandExecutor::print() const
{
    std::cout << this->element;
}

void CommandExecutor::select(const char* id, const char* key) const
{
    if(!this->element.getAttributeValue(id, key))
    {
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
        return;
    }

    std::cout << this->element.getAttributeValue(id, key) << std::endl;
}

void CommandExecutor::set(const char* id, const char* key, const char* value)
{
    bool flag = this->element.setAttributeValue(id, key, value);
    
    if(!flag) 
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
    
    this->isSaved = false;
}

Array<Attribute> CommandExecutor::children(const char* id) const
{
    return this->element.getChildrenAttributes(id);
}

// n > 0
void CommandExecutor::child(const char* id, unsigned int n) const
{
    if(n == 0)
    {
        std::cout << "Invalid n!" << std::endl;
        return;
    }

    bool isFound = false;

    Element child = this->element.getChild(id, n, isFound);

    if(isFound) std::cout << child;
    else std::cout << "The nth successor has not been found!" << std::endl;
}

void CommandExecutor::text(const char* id) const
{
    if(!this->element.getText(id))
    {
        std::cout << "There is no element with this id or it has no text!" << std::endl;
        return;
    }

    std::cout << this->element.getText(id) << std::endl;
}

void CommandExecutor::deleteAttribute(const char* id, const char* key)
{
    bool flag = this->element.deleteAttribute(id, key);
    
    if(!flag) 
        std::cout << "There is no element with this id whose attribute has this key!" << std::endl;
    
    this->isSaved = false;
}

void CommandExecutor::newchild(const char* id)
{
    bool flag = this->element.addNestedElement(id);
    
    if(!flag) 
        std::cout << "There is no element with this id!" << std::endl;

    this->isSaved = false;
}

bool CommandExecutor::isValidCommand(const CommandParser& parser) const
{
    char* command = new(std::nothrow) char[this->MAX_LEN];
    if(!command)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return false;
    }

    strcpy(command, parser[0]);
    Helper::inLowerCase(command);

    int numberOfArgs = parser.getNumberOfArguments();

    if((strcmp(command, "open") == 0 && numberOfArgs == 2) || 
        (strcmp(command, "save as") == 0 && numberOfArgs == 2))
    {   
        delete[] command;
        command = nullptr;
        return Helper::isValidFileName(parser[1], this->MAX_LEN);
    }
    else if((strcmp(command, "close") == 0 && numberOfArgs == 1) ||
            (strcmp(command, "save") == 0 && numberOfArgs == 1) ||
            (strcmp(command, "help") == 0 && numberOfArgs == 1) ||
            (strcmp(command, "exit") == 0 && numberOfArgs == 1))
    {
        delete[] command;
        command = nullptr;
        return true;
    }
    else if((strcmp(command, "print") == 0 && numberOfArgs == 1) ||
            (strcmp(command, "select") == 0 && numberOfArgs == 3) ||
            (strcmp(command, "set") == 0 && numberOfArgs == 4) ||
            (strcmp(command, "children") == 0 && numberOfArgs == 2) ||
            (strcmp(command, "child") == 0 && numberOfArgs == 3) ||
            (strcmp(command, "text") == 0 && numberOfArgs == 2) ||
            (strcmp(command, "delete") == 0 && numberOfArgs == 3) ||
            (strcmp(command, "newchild ") == 0 && numberOfArgs == 2))
    {
        delete[] command;
        command = nullptr;
        return true;
    }
    
    delete[] command;
    command = nullptr;
    return false;
}

void CommandExecutor::execute(const CommandParser& parser)
{
    if(!this->isValidCommand(parser))
    {
        std::cout << "Invalid command!" << std::endl;
        return;
    }

    char* command = new(std::nothrow) char[this->MAX_LEN];
    if(!command)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return;
    }

    strcpy(command, parser[0]);
    Helper::inLowerCase(command);

    if(this->isFirstCommand && strcmp(command, "open") != 0 && 
                    strcmp(command, "help") != 0 && strcmp(command, "exit") != 0)
    {
        std::cout << "To continue, you must first open a file!" <<std::endl;

        delete[] command;
        command = nullptr;
        
        return;
    }

    if(strcmp(command, "open") == 0)
    {
        this->open(parser[1]);
    }
    else if(strcmp(command, "close") == 0)
    {
        this->close();
    }
    else if(strcmp(command, "save") == 0)
    {
        this->save();
    }
    else if(strcmp(command, "save as") == 0)
    {
        this->saveAs(parser[1]);
    }
    else if(strcmp(command, "help") == 0)
    {
        this->help();
    }
    else if(strcmp(command, "exit") == 0)
    {
        if(!this->isSaved)
        {
            char buffer[this->MAX_LEN];
            std::cout << "You have an open file with unsaved changes, please select close, save or save as first.\n";
            std::cin.getline(buffer, this->MAX_LEN);

            CommandParser p(buffer);
            if(!this->isValidCommand(p))
            {
                std::cout << "Invalid command!" << std::endl;

                this->close();
                
                delete[] command;
                command = nullptr;

                std::cout << "Exiting program..." << std::endl;
                std::exit(0);
            }

            this->exit(p);
        }

        std::cout << "Exiting program..." << std::endl;
        
        delete[] command;
        command = nullptr;
        
        std::exit(0);
    }
    else if(strcmp(command, "print") == 0)
    {
        this->print();
    }
    else if(strcmp(command, "select") == 0)
    {
        this->select(parser[1], parser[2]);
    }
    else if(strcmp(command, "set") == 0)
    {
        this->set(parser[1], parser[2], parser[3]);
    }
    else if(strcmp(command, "children") == 0)
    {
        this->children(parser[1]);
    }
    else if(strcmp(command, "child") == 0)
    {
        unsigned int n = Helper::toNumber(parser[2]);
        this->child(parser[1], n);
    }
    else if(strcmp(command, "text") == 0)
    {
        this->text(parser[1]);
    }
    else if(strcmp(command, "delete") == 0)
    {
        this->deleteAttribute(parser[1], parser[2]);
    }
    else if(strcmp(command, "newchild") == 0)
    {
        this->newchild(parser[1]);
    }

    delete[] command;
    command = nullptr;
}