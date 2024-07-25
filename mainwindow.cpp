#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    exportGPIO(963);
    exportGPIO(962);
    setGPIODirection(963,"out");
    setGPIODirection(962,"out");

    vac = new Vaccum;
    h = new hwHandler;

    preset = ui->label->text().toInt();
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

void MainWindow::on_pushButton_clicked()
{
    writeGPIO(963,1);
    usleep(5000);
    writeGPIO(963,0);

    h->ai_on();
    h->ai_preset_count(preset);

    int flow=90+ (int)(preset* 1.5);
    h->write_motor(0x01,0x03,flow);

    int actual;
    actual=0;
    for(int i=0; i<10; i++)
    {
        actual += vac->convert(CHANNEL_2) * 0.1894;
    }
    actual = static_cast<int>(actual/10);

    qDebug()<<actual;
    ui->label_2->setText(QString::number(actual));

    h->ai_actual_count(actual);


}

void MainWindow::on_pushButton_2_clicked()
{
    writeGPIO(962,1);
    usleep(5000);
    writeGPIO(962,0);

    h->ai_on();
    h->ai_preset_count(preset);

    int flow=90+ (int)(preset* 1.5);
    h->write_motor(0x01,0x03,flow);

    int actual;
    actual=0;
    for(int i=0; i<10; i++)
    {
        actual += vac->convert(CHANNEL_2) * 0.1894;
    }
    actual = static_cast<int>(actual/10);

    qDebug()<<actual;
    ui->label_2->setText(QString::number(actual));

    h->ai_actual_count(actual);



}
void MainWindow::on_pushButton_3_clicked()
{
    preset = ui->label->text().toInt();
    preset -= 5;
    ui->label->setText(QString::number(preset));
}

void MainWindow::on_pushButton_4_clicked()
{
    preset = ui->label->text().toInt();
    preset += 5;
    ui->label->setText(QString::number(preset));

}

void MainWindow::on_pushButton_5_clicked()
{
    h->ai_off();
    h->ai_preset_count(0);
    h->write_motor(0x00, 0x03, 0);
    h->ai_actual_count(0);
    ui->label_2->setText("0");
}
