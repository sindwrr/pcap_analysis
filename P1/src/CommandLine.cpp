#include "CommandLine.h"

CommandLine::CommandLine(int argc, char** argv): argc(argc), argv(argv) {};

// возвращает кол-во аргументов
int CommandLine::getArgc()
{
    return argc;
}

// возвращает массив аргументов
char** CommandLine::getArgv()
{
    return argv;
}

// возвращает индекс аргумента в командной строке
int CommandLine::find(std::string argument)
{
    for (int i = 0; i < argc; i++)
        if (argv[i] == argument)
            return i;

    return -1;
}