#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Sender");//Definitir titulo da janela
    QFont fonte = ui->label->font();//Pegar a fonte utilizada no label
    fonte.setPointSize(12);//Definir o tamanho
    ui->label->setFont(fonte);//atualizar a fonte
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()// clique do botao
{
    QFile data ("../dataLog.txt");//nome do arquivo e diretório
    QString mensagem = ui->textEdit->toPlainText();//lê a mensagem digitada
    if(!mensagem.isEmpty()){//testa se esta vazia
        if(!data.open(QFile::Append|QFile::Text)){//erro caso não seja possivel abrir o arquivo
            QMessageBox::warning(this,"Erro:","não foi possível abrir arquivo");
        }
        QTextStream saida(&data);
        mensagem ="["+QTime::currentTime().toString() + "]:  "+mensagem;//Hora atual + mensagem lida
        saida << mensagem+"\n";// mensagem a ser inserida no arquivo
        data.flush();
        data.close();
        ui->listWidget->addItem(mensagem);//Adiciona a mensagem lida a lista de widgets
        ui->textEdit->clear();//limpa o campo de texto
        ui->textEdit->setFocus();//direciona o cursor para o campo de texto
        }
}
