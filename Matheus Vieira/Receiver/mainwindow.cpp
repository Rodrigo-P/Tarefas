#include "mainwindow.h"
#include "ui_mainwindow.h"

bool botao = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Receiver");
    QFont fonte = ui->label->font();
    fonte.setPointSize(12);
    ui->label->setFont(fonte);
    tempo = new QTimer();
    connect(tempo,SIGNAL(timeout()),this,SLOT(attMsg()));
    tempo->start(5);
    QFile arquivo("../dataLog.txt");
    if(!arquivo.open(QFile::WriteOnly)){
        QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo");
    }
    QTextStream saida(&arquivo);
    saida << "======= inicio da sessao =======\n";
    arquivo.flush();
    arquivo.close();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(botao){
        botao = false;
        ui->pushButton->setText("Iniciar Leitura");
    }
    else{
        botao = true;
        ui->pushButton->setText("Encerrar leitura");
    }
}

void MainWindow::attMsg(){
    if(botao){
        ui->listWidget->clear();
        QFile arquivo("../dataLog.txt");
        if(!arquivo.open(QFile::ReadOnly)){
            QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo");
        }
        else{
            QTextStream entrada(&arquivo);
            while(!entrada.atEnd()){
                QString texto = entrada.readLine();
                ui->listWidget->addItem(texto);
            }
            arquivo.close();
        }
    }
}
