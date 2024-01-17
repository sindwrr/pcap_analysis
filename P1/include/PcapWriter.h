#ifndef PCAP_WRITER_H
#define PCAP_WRITER_H

#include <pcpp/PcapFileDevice.h>

// обертка над классом библиотеки, записывает данные в pcap файл
class PcapWriter: public pcpp::PcapFileWriterDevice
{
public:
    PcapWriter(const char* filename): pcpp::PcapFileWriterDevice(filename) {};
    ~PcapWriter() {this->close();};
};

#endif