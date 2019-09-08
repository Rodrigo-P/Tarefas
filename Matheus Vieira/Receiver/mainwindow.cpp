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
