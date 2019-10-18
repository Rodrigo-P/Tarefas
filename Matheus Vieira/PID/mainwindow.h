#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "comunicacao.h"
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool lendo = false;
    QSerialPort *serial = new QSerialPort();
    Comunicacao* canal = new Comunicacao(serial);
    QByteArray conteudo;
    QString valor;
    QStringList dispositivos;
    int cont = 0;
    QByteArray array;
    bool initWrite = true;
    QChar a = '$';
    QVector<double> x,MV;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private slots:
    void attValores();
    void attPortas();

private:
    Ui::MainWindow *ui;
     QTimer *tempo;
};

#endif // MAINWINDOW_H
