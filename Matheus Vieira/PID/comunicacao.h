#ifndef COMUNICACAO_H
#define COMUNICACAO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtDebug>
class Comunicacao
{
public:
    QSerialPort *Serial;
    Comunicacao(QSerialPort *my);
    QStringList dispositivos();
    bool conectarDipositivo(QString Porta, int boundrate);
    bool desconectar();
    void write(const QByteArray &data);
    QByteArray read();
};

#endif // COMUNICACAO_H
