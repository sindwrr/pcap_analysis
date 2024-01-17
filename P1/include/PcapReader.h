#ifndef PCAP_READER_H
#define PCAP_READER_H

#include <pcpp/PcapFileDevice.h>

// обертка над классом библиотеки, читает данные из pcap файла
class PcapReader: public pcpp::PcapFileReaderDevice
{
public:
    PcapReader(const char* filename): pcpp::PcapFileReaderDevice(filename) {};
    ~PcapReader() {this->close();};
};

#endif