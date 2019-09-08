#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>// Biblioteca necessária para leitura e escrita de arquivos
#include <QTime>// biblioteca para pegar o tempo atual do computador
#include <QMessageBox>//Biblioteca para inserir a mensagem de erro
#include <QTextStream>//Biblioteca para inserir Strings no arquivo

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
