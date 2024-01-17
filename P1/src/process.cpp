#include <iostream>

#include "funcs.h"
#include "defaultValues.h"
#include "CommandLine.h"
#include "PacketCapturer.h"
#include "PcapWriter.h"
#include "PcapReader.h"
#include "PacketParser.h"
#include "CsvWriter.h"

// функция основной обработки
int process(int argc, char *argv[])
{
    CommandLine cl(argc, argv); // объект класса командной строки

    // выделяем названия pcap и csv файлов из аргументов строки
    // (если не указаны - берем по умолчанию)

    const char* pcapFile = cl.find("-p") > 0 ? 
                           argv[cl.find("-p") + 1] : DEFAULT_PCAP_FILE;

    const char* csvFile = cl.find("-f") > 0 ? 
                          argv[cl.find("-f") + 1] : DEFAULT_CSV_FILE;

    // если указан флаг захвата, производим захват пакетов
    if (cl.find("-c") > 0)
    {
        pcpp::PcapLiveDevice* device; // интерфейс для захвата
        PacketCapturer capturer(device); // объект-"захватчик"
        
        // выделяем параметры для "захватчика"
        // если что-то не так, завершаем программу
        if (!capturer.setParams(cl))
            return 1;

        // открываем интерфейс и начинаем захват пакетов с него
        if (capturer.openDevice())
            capturer.capturePackets();
        else
        {
            std::cerr << "Ошибка открытия устройства для захвата пакетов!" 
                      << std::endl;
            return 1;
        }

        capturer.printPacketsNum(); // выводим кол-во захваченных пакетов

        // открываем pcap-файл для записи пакетов
        PcapWriter pcapWriter(pcapFile);
        if (!pcapWriter.open())
        {
            std::cerr << "Ошибка открытия pcap-файла для записи!" << std::endl;
            return 1;
        }

        // записываем пакеты
        pcapWriter.writePackets(capturer.getPacketVector());
    }

    // открываем pcap-файл для чтения
    PcapReader reader(pcapFile);
    if (!reader.open())
    {
        std::cerr << "Ошибка открытия pcap-файла для чтения!" << std::endl;
        return 1;
    }

    PacketParser parser(&reader); // парсер пакетов

    // преобразуем заголовки пакетов в требуемые потоки
    auto params = parser.convertToNetRecords();
    parser.printInfo(); // выводим кол-во IPv4 пакетов и потоков

    // записываем полученный вектор в csv-файл
    CsvWriter csv(csvFile);
    csv.writeRows(params);

    return 0;
}