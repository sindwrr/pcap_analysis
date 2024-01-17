#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <fstream>
#include <vector>
#include <array>
#include <string>

// класс для записи потоков в csv-файл
class CsvWriter: public std::ofstream
{
public:
    CsvWriter(std::string file): std::ofstream(file, std::ios::out) {};
    static std::string intToIPv4(uint32_t);
    void writeRow(const std::array<uint32_t, 6>&);
    void writeRows(const std::vector<std::array<uint32_t, 6>>&);
    ~CsvWriter();
};

#endif