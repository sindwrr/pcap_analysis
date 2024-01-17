#include "funcs.h"

// точка входа в проект
int main(int argc, char *argv[])
{
    // проводим юнит-тесты
    tests();
    
    // совершаем основную обработку и возвращаем результат
    // (0 - нормальное завершение, 1 - с ошибками)
    int exitCode = process(argc, argv);
    return exitCode;
}