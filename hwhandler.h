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

#define VIT_ONOFF_REG               24
#define VIT_ONTIME_REG              25
#define VIT_COUNT_REG               26

#define ON_MASK                     0x01
#define OFF_MASK                    0x00

#define VSO_PWM_ON_REG              40
#define VSO_PWM_PERIOD_REG          42

#define DIA_ONOFF_REG               20
#define DIA_COUNT_REG               22

#define AI_ONOFF_REG                44
#define AI_PRESET_REG               48
#define AI_COUNT_REG                50

#define SIL_OIL_REG                 28

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
    int memfd;
    static void vit_on(int count);
    static void vit_off();
    static void vit_ontime(int ontime);

    static void vso_off();
    static void vso_ontime(int ontime);
    static void vso_period(int count);

    static void dia_on();
    static void dia_off();
    static void dia_count(int count);

    static void ai_on();
    static void ai_off();
    static void ai_preset_count(int count);
    static void ai_actual_count(int count);

    static void siloil_on();
    static void siloil_off();

    void write_motor(uint16_t status, uint16_t direction, uint16_t value);


signals:

};
#endif // HWHANDLER_H



