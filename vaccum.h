#ifndef VACCUM_H
#define VACCUM_H

#include <QObject>
#include <QVector>
#include <QTimer>

class Vaccum : public QObject
{
    Q_OBJECT
public:
    Vaccum();
    ~Vaccum();
    void initSPI();
    int convert(uint8_t channel);

private:
    QTimer *timer;
    int spi_fd;

};

#endif // VACCUM_H
