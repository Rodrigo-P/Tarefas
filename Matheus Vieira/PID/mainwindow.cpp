#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


int k = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Controle PID");
    QSerialPort *Serial = new QSerialPort(this);
    Comunicacao *Canal = new Comunicacao(Serial);
    QStringList dispositivos = Canal->dispositivos();
    foreach(QString dispositivo, dispositivos){
        ui->comboBox->addItem(dispositivo);
    }
    tempo = new QTimer();
    connect(tempo,SIGNAL(timeout()),this,SLOT(attPortas()));
    tempo->start(1000);
    array.append(a);
    ui->Plot->addGraph();
    ui->Plot->graph(0)->setPen(QPen(Qt::blue));
    ui->Plot->setInteraction(QCP::iRangeDrag,true);
    ui->Plot->setInteraction(QCP::iRangeZoom,true);
    ui->P->setReadOnly(true);
    ui->I->setReadOnly(true);
    ui->D->setReadOnly(true);
    ui->MotorV->setReadOnly(true);
    ui->MotorRad->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->comboBox->currentText() != "" && lendo == false){
        if(canal->conectarDipositivo(ui->comboBox->currentText(),ui->bound->value())){
            connect(canal->Serial,SIGNAL(readyRead()),this,SLOT(attValores()));
            qDebug() << ui->comboBox->currentText();
            qDebug() << ui->bound->value();
            initWrite = true;
            ui->pushButton->setText("Parar");
            ui->bound->setReadOnly(true);
            lendo = true;
            ui->Plot->yAxis->setRange(0,5);
            ui->Plot->xAxis->setRange(0,10);
            ui->Plot->replot();
            ui->Plot->update();
        }
    }else if(lendo){
        canal->desconectar();
        k = 0;
        x.clear();
        MV.clear();
        x.resize(0);
        MV.resize(0);
        qDebug() << MV;
        conteudo = "";
        lendo = false;
        ui->bound->setReadOnly(false);
        ui->pushButton->setText("Iniciar");
    }else{
        QMessageBox *erro = new QMessageBox(this);
        erro->setText("Selelcione uma porta para iniciar");
        erro->exec();
    }
}


void MainWindow::attPortas(){
    QStringList dispositivos2 = canal->dispositivos();
    if(dispositivos2 != dispositivos){
        ui->comboBox->clear();
        foreach(QString dispositivo, dispositivos2){
            ui->comboBox->addItem(dispositivo);
        }
        dispositivos = dispositivos2;
    }
}


typedef struct data{
    float P;
    float I;
    float D;
    float In;
    float temp;
    int vel;
}data;

typedef union dataUnion{
    data dataValue;
    QByteArray byteArray[sizeof (struct data)];
}dataUnion;

void MainWindow::attValores(){
    if(lendo){
        conteudo  = canal->read();
        struct data* m = reinterpret_cast<struct data*>(conteudo.data());
        if(conteudo.size() == 24){
            qDebug() << conteudo;
            qDebug() << m->temp;
            qDebug() << m->P;
            qDebug() << m->I;
            qDebug() << m->D;
            qDebug() << m->In;
            qDebug() << m->vel;
            ui->MotorV->setText(QString::number(double(m->In)));
            ui->P->setText(QString::number(double(m->P)));
            ui->I->setText(QString::number(double(m->I)));
            ui->D->setText(QString::number(double(m->D)));
            ui->MotorV->setText(QString::number(double(m->In)));
            ui->MotorRad->setText(QString::number(double(m->vel)));
            x.append(double(m->temp));
            MV.append(double(m->vel));
            ui->Plot->graph(0)->setData(x,MV);
            ui->Plot->replot();
            ui->Plot->update();
            if(k>21){
                ui->Plot->yAxis->setRange(MV[k-20]-10,MV[k]+10);
                ui->Plot->xAxis->setRange(x[k-20],x[k]);
            }else{
                ui->Plot->yAxis->setRange(MV[0]-10,MV[k]+10);
                ui->Plot->xAxis->setRange(x[0],x[k]);
            }
            valor = "";
            k++;
        }
        conteudo = "";
    }
}
