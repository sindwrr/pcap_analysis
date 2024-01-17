#include <cassert> 

#include "funcs.h"
#include "CommandLine.h"
#include "CsvWriter.h"

// юнит-тесты методов классов
void tests()
{
    char* argv[] = {(char*)"./exec", (char*)"-c", (char*)"-i", 
                    (char*)"-eth0", (char*)"-d", (char*)"15"};
    int argc = 6;
    CommandLine clTest(argc, argv);
    assert(clTest.find("-c") == 1);
    assert(clTest.find("-d") == 4);
    assert(clTest.find("-f") == -1);

    assert(CsvWriter::intToIPv4(0) == "0.0.0.0");
    assert(CsvWriter::intToIPv4(4294967295) == "255.255.255.255");
    assert(CsvWriter::intToIPv4(16820416) == "192.168.0.1");
    assert(CsvWriter::intToIPv4(1775950252) == "172.217.218.105");
    assert(CsvWriter::intToIPv4(182039765) == "213.180.217.10");
}