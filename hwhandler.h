#ifndef HWHANDLER_H
#define HWHANDLER_H

#include <QThread>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTime>

#define XPAR_AXI_COMBINED_BASEADDR 0x43C40000;
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define ON_MASK                     0x01
#define OFF_MASK                    0x00

#define AI_ONOFF_REG                44
#define AI_PRESET_REG               48
#define AI_COUNT_REG                50

#define CHANNEL_0                   0x97
#define CHANNEL_1                   0xD7
#define CHANNEL_2                   0xA7
#define CHANNEL_3                   0xE7

#define MOT_CTRL_REG                32
#define MOT_COUNT_REG               36


class hwHandler: public QThread
{
    Q_OBJECT

public:
    explicit hwHandler(QObject *parent = 0);
    static void ai_on();
    static void ai_off();
    static void ai_preset_count(int count);
    static void ai_actual_count(int count);
    void write_motor(uint16_t status, uint16_t direction, uint16_t value);
    int memfd;


signals:

};
#endif // HWHANDLER_H



