#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    exportGPIO(960);
    setGPIODirection(960,"out");
    writeGPIO(960,1);
    usleep(5000);
    writeGPIO(960,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exportGPIO(int pin) {
    std::ofstream exportFile("/sys/class/gpio/export");
    if (!exportFile.is_open()) {
        std::cerr << "Unable to export GPIO" << std::endl;
        return;
    }
    exportFile << pin;
    exportFile.close();
}

void MainWindow::setGPIODirection(int pin, const std::string& direction) {
    std::ofstream directionFile("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
    if (!directionFile.is_open()) {
        std::cerr << "Unable to set GPIO direction" << std::endl;
        return;
    }
    directionFile << direction;
    directionFile.close();
}

void MainWindow::writeGPIO(int pin, int value) {
    std::ofstream valueFile("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
    if (!valueFile.is_open()) {
        std::cerr << "Unable to write to GPIO" << std::endl;
        return;
    }
    valueFile << value;
    valueFile.close();
}
