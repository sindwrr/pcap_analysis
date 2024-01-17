#ifndef PACKET_CAPTURER_H
#define PACKET_CAPTURER_H

#include <pcpp/PcapLiveDevice.h>
#include "CommandLine.h"

// класс для захвата пакетов
class PacketCapturer
{
private:
    pcpp::PcapLiveDevice* device; // сетевой интерфейс
    pcpp::RawPacketVector rawPackets; // вектор необработанных пакетов
    int duration; // время захвата пакетов

public:
    PacketCapturer(pcpp::PcapLiveDevice* device): device(device) {};
    pcpp::RawPacketVector getPacketVector();
    bool openDevice() {return device->open();};
    void capturePackets();
    bool setParams(CommandLine cl);
    void printPacketsNum();
    pcpp::PcapLiveDevice* getDevice() {return device;};
    ~PacketCapturer() = default;
};

#endif