#include "iniciar.h"
#include "ui_iniciar.h"
#include "comunicacao.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "mainwindow.h"



Iniciar::Iniciar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iniciar)
{
    ui->setupUi(this);
    QSerialPort *Serial = new QSerialPort(this);
    Comunicacao *Canal = new Comunicacao(Serial);
    QStringList dispositivos = Canal->dispositivos();
    foreach(QString dispositivo, dispositivos){
        ui->comboBox->addItem(dispositivo);
    }
}

Iniciar::~Iniciar()
{
    delete ui;
}

void Iniciar::on_buttonBox_accepted()
{
    QString arquivo;
    if(ui->sim->isChecked()){
        arquivo = ui->nome->text();
    }
    int boundRate = (ui->bound->text()).toInt();

}
