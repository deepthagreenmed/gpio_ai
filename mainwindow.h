#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "vaccum.h"

#define CHANNEL_2       0xA7

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exportGPIO(int pin);
    void setGPIODirection(int pin, const std::string& direction);
    void writeGPIO(int pin, int value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Vaccum *vac;
};
#endif // MAINWINDOW_H
