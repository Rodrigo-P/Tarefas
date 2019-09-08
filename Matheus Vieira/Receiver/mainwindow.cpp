#include "mainwindow.h"
#include "ui_mainwindow.h"

bool botao = false;//define se o botão está ou não pressionado

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Receiver");//Define o titulo da tela principal
    QFont fonte = ui->label->font();//Pegar a fonte utilizada no label
    fonte.setPointSize(12);//Definir o tamanho
    ui->label->setFont(fonte);//atualizar a fonte
    tempo = new QTimer();//define o timer
    connect(tempo,SIGNAL(timeout()),this,SLOT(attMsg()));// linka o tempo a função de atualizar mensagens
    tempo->start(5);//define de quanto em quanto tempo as mensagens devem ser atualizadas (5ms)
    QFile arquivo("../dataLog.txt");//nome do arquivo e diretório
    if(!arquivo.open(QFile::WriteOnly)){//erro caso não seja possivel abrir o arquivo
        QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo");
    }
    QTextStream saida(&arquivo);
    saida << "======= inicio da sessao =======\n";// texto a ser escrito inicialmente
    arquivo.flush();
    arquivo.close();//fecha e salva o arquivo
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(botao){// altera o estado do botao de pressionado para nao pressionado
        botao = false;
        ui->pushButton->setText("Iniciar Leitura");
    }
    else{
        botao = true;
        ui->pushButton->setText("Encerrar leitura");
    }
}

void MainWindow::attMsg(){
    if(botao){// testa se botão está pressionado
        ui->listWidget->clear();//limpa a lista
        QFile arquivo("../dataLog.txt");//nome e diretório do arquivo
        if(!arquivo.open(QFile::ReadOnly)){//erro caso não seja possivel abrir o arquivo
            QMessageBox::warning(this,"ERRO","Não foi possível abrir o arquivo");
        }
        else{
            QTextStream entrada(&arquivo);//define o arquivo como uma entrada
            while(!entrada.atEnd()){//lê o arquivo até o final
                QString texto = entrada.readLine();//lê linha por linha
                ui->listWidget->addItem(texto);//Adiciona o texto lido a lista de widgets
            }
            arquivo.close();//fecha o arquivo
        }
    }
}
