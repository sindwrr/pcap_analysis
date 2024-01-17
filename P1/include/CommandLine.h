#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>

// класс для операций над командной строкой запуска программы
class CommandLine
{  
private:
    int argc; // кол-во аргументов
    char** argv; // массив аргументов
public:
    CommandLine(int argc, char** argv);
    int getArgc();
    char** getArgv();
    int find(std::string argument);
    ~CommandLine() = default;
};

#endif
