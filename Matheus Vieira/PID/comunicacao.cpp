#include "comunicacao.h"
#include <QDebug>
Comunicacao::Comunicacao(QSerialPort *my)
{
    Serial = my;
}

QStringList Comunicacao::dispositivos()
{
    QStringList dispositivosEncontrados;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            dispositivosEncontrados.append(info.portName());
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
                serial.close();
        }
    }
    return dispositivosEncontrados;
}

bool Comunicacao::conectarDipositivo(QString Port,int bd)
{
    /* Device Serial Port */
    Serial->setPortName(Port);
    qDebug() << "Dispositivo Porta Serial: " << Port;
        switch (bd) {
        case 2400:
            Serial->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            Serial->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            Serial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            Serial->setBaudRate(QSerialPort::Baud19200);
            break;
        case 115200:
            Serial->setBaudRate(QSerialPort::Baud115200);
            break;
        }

        Serial->setFlowControl(QSerialPort::NoFlowControl);
        Serial->setDataBits(QSerialPort::Data8);
        Serial->setParity(QSerialPort::NoParity);
        Serial->setStopBits(QSerialPort::OneStop);


        if(Serial->open(QIODevice::ReadWrite)) {
            qDebug() << "Porta serial aberta com sucesso!";
            return true;
        }
        else {
            qDebug() << "Falha ao abrir porta serial!";
            qDebug() << "Erro: " << Serial->error();
            return false;
        }


}

bool Comunicacao::desconectar()
{
    Serial->clear();
    Serial->close();
    if(Serial->error() == 0 || !Serial->isOpen()) {
        qDebug() << "Porta serial fechada com sucesso!";
        return true;
    }
    else {
        qDebug() << "Falha ao fechar a porta serial! ERRO: " << Serial->error();
        return false;
    }

}


QByteArray Comunicacao::read()
{
     QByteArray bufferSerial;
     if(Serial->bytesAvailable() >= 24){
        bufferSerial += Serial->read(24);
     }
     return bufferSerial;
}

void Comunicacao::write(const QByteArray &data)
{
    Serial->write(data);
}

