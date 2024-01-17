#include "CsvWriter.h"

// переводит 32-битное число в строку формата IPv4
std::string CsvWriter::intToIPv4(uint32_t num) 
{
    std::string result;
    for (int i = 3; i >= 0; --i) 
    {
        if (i < 3)
            result += '.';

        int octet = (num >> (8 * (3 - i))) & 0xFF;
        result += std::to_string(octet);
    }

    return result;
}

// записывает поток в csv
void CsvWriter::writeRow(const std::array<uint32_t, 6>& row)
{
    *this << intToIPv4(row[0]) << ","
          << intToIPv4(row[1]) << ","
          << row[2] << ","
          << row[3] << ","
          << row[4] << ","
          << row[5] << "\n";
}

// записывает вектор потоков потоков в csv
void CsvWriter::writeRows(const std::vector<std::array<uint32_t, 6>>& params)
{
    for (const auto &row : params)
        writeRow(row);
}

// при уничтожении объекта закрываем csv
CsvWriter::~CsvWriter()
{
    this->close();
}