#include <iostream>
#include <vector>
#include <array>
#include <set>

#include <pcpp/Packet.h>
#include <pcpp/IPv4Layer.h>
#include <pcpp/TcpLayer.h>
#include <pcpp/UdpLayer.h>

#include "PacketParser.h"

using std::array;
using std::set;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

// рассчитывает требуемые потоки 
void PacketParser::calculate(const vector<array<uint32_t, 5>>& packets, 
                             const array<uint32_t, 4>& conn,
                             vector<array<uint32_t, 6>>& netRecords)
{
    uint32_t packet_count{}, byte_count{};
    array<uint32_t, 4> curr;

    // для каждого пакета из вектора пакетов...
    for (auto &pkt : packets)
    {
        curr = {pkt[0], pkt[1], pkt[2], pkt[3]};

        // ...сравниваем его с потоком и увеличиваем кол-во
        // соответствующих пакетов и байт
        if (curr == conn)
        {
            packet_count++;
            byte_count += pkt[4];
        }
    }

    // добавляем в конечный вектор полученную запись
    netRecords.push_back({conn[0], conn[1], conn[2], conn[3], 
                          packet_count, byte_count});
}

vector<array<uint32_t, 6>> PacketParser::convertToNetRecords()
{
    pcpp::RawPacket rawPacket; // необработанный пакет
    pcpp::Packet parsedPacket; // обработанный пакет (с возможностью 
                               // прочтения заголовка)
    pcpp::IPv4Address srcIP, dstIP;
    uint16_t srcPort, dstPort, bytesNum;

    // временное множество для хранения уникальных совокупностей IP и портов
    set<array<uint32_t, 4>> temp_set;

    // поочередно читаем каждый пакет
    while (reader->getNextPacket(rawPacket))
    {
        bytesNum = rawPacket.getRawDataLen();
        parsedPacket.setRawPacket(&rawPacket, false);

        // отбираем только IPv4 пакеты
        if (parsedPacket.isPacketOfType(pcpp::IPv4))
        {
            // присваиваем IP источника и получателя
            srcIP = parsedPacket.getLayerOfType<pcpp::IPv4Layer>()->getSrcIPv4Address();
            dstIP = parsedPacket.getLayerOfType<pcpp::IPv4Layer>()->getDstIPv4Address();

            // в зависимости от протокола 4-го уровня присваиваем порты
            if (parsedPacket.isPacketOfType(pcpp::TCP))
            {
                srcPort = parsedPacket.getLayerOfType<pcpp::TcpLayer>()->getSrcPort();
                dstPort = parsedPacket.getLayerOfType<pcpp::TcpLayer>()->getDstPort();
            }
            else if (parsedPacket.isPacketOfType(pcpp::UDP))
            {
                srcPort = parsedPacket.getLayerOfType<pcpp::UdpLayer>()->getSrcPort();
                dstPort = parsedPacket.getLayerOfType<pcpp::UdpLayer>()->getDstPort();
            }

            // сохраняем полученную информацию в вектор и множество
            packetsInfo.push_back({srcIP.toInt(), 
                                   dstIP.toInt(), 
                                   srcPort, 
                                   dstPort, 
                                   bytesNum});
            temp_set.insert({srcIP.toInt(), dstIP.toInt(), srcPort, dstPort});
        }
    }

    // копируем элементы множества в вектор для более удобной обработки
    uniqueConns.assign(temp_set.begin(), temp_set.end());

    // для каждой совокупности IP и портов вычисляем кол-во
    // переданных пакетов и байт и заносим результат в finalRecords
    for (auto &conn : uniqueConns)
        calculate(packetsInfo, conn, finalRecords); 

    return finalRecords;
}

void PacketParser::printInfo()
{
    cout << "Обработано IPv4-пакетов: " << packetsInfo.size() << endl;
    cout << "Уникальных соединений: " << uniqueConns.size() << endl;
}