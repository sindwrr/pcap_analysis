#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include "PcapReader.h"
#include <vector>
#include <array>

// класс для обработки пакетов
class PacketParser
{
private:
    PcapReader* reader; // "читатель" pcap-файла

    // вектор массивов с информацией о каждом пакете вида:
    // (srcIP, dstIP, srcPort, dstPort, bytesNum)
    std::vector<std::array<uint32_t, 5>> packetsInfo;

    // вектор массивов с уникальными комбинациями вида:
    // (srcIP, dstIP, srcPort, dstPort)
    std::vector<std::array<uint32_t, 4>> uniqueConns;

    // вектор массивов с информацией о требуемых потоках вида:
    // (srcIP, dstIP, srcPort, dstPort, packetsNum, bytesNum)   
    std::vector<std::array<uint32_t, 6>> finalRecords;
public:
    PacketParser(PcapReader* read): reader(read) {};

    static void calculate(const std::vector<std::array<uint32_t, 5>>&, 
                          const std::array<uint32_t, 4>&,
                          std::vector<std::array<uint32_t, 6>>&); 

    std::vector<std::array<uint32_t, 6>> convertToNetRecords();

    void printInfo();

    ~PacketParser() = default;
};

#endif