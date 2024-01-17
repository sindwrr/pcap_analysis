#include <iostream>

#include <pcpp/PcapLiveDeviceList.h>
#include <pcpp/SystemUtils.h>

#include "defaultValues.h"
#include "PacketCapturer.h"

// возвращает вектор необработанных пакетов
pcpp::RawPacketVector PacketCapturer::getPacketVector()
{
    return rawPackets;
}

// захватывает пакеты с интерфейса device в течение duration
void PacketCapturer::capturePackets()
{
    device->startCapture(rawPackets);
    pcpp::multiPlatformSleep(duration);
    device->stopCapture();
}

// устанавливает параметры из командной строки
bool PacketCapturer::setParams(CommandLine cl)
{
    int argc = cl.getArgc();
    char** argv = cl.getArgv();

    // если интерфейс указан пользователем, то он присваивается,
    // иначе присваивается номер по умолчанию из defaultValues.h
    device = cl.find("-i") != -1 ? 
                pcpp::PcapLiveDeviceList::getInstance()
                .getPcapLiveDeviceByIpOrName(argv[cl.find("-i") + 1]) :
                pcpp::PcapLiveDeviceList::getInstance()
                .getPcapLiveDevicesList().at(DEFAULT_INTERFACE);

    if (device == NULL)
    {
        std::cerr << "Заданный интерфейс не найден!" << std::endl;
        return 0;
    }

    // если время указано пользователем, то оно присваивается,
    // иначе присваивается по умолчанию из defaultValues.h
    try 
    {
        duration = cl.find("-d") > 0 ? std::stoi(argv[cl.find("-d") + 1]) :
                                       DEFAULT_SNIFF_TIME;
    }
    catch(...)
    {
        std::cerr << "Ошибка обработки времени захвата!" << std::endl;
        return 0;
    }
    
    return 1;
}

void PacketCapturer::printPacketsNum()
{
    std::cout << "Захвачено пакетов: " << rawPackets.size() << std::endl;
}
