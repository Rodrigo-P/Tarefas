#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Sender");
    QFont fonte = ui->label->font();
    fonte.setPointSize(12);
    ui->label->setFont(fonte);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFile data ("../dataLog.txt");
    QString mensagem = ui->textEdit->toPlainText();
    if(!mensagem.isEmpty()){
        if(!data.open(QFile::Append|QFile::Text)){
            QMessageBox::warning(this,"Erro:","não foi possível abrir arquivo");
        }
        QTextStream saida(&data);
        mensagem ="["+QTime::currentTime().toString() + "]:  "+mensagem;
        saida << mensagem+"\n";
        data.flush();
        data.close();
        ui->listWidget->addItem(mensagem);
        ui->textEdit->clear();
        ui->textEdit->setFocus();
        }
}
