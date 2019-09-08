#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>//Biblioteca para pegar o tempo atual e atualizar as mensagens periodicamente
#include <QMessageBox>//Biblioteca para criar mensagens em uma caixa
#include <QFile>//Biblioteca para leitura e escrita de arquivos
#include <QTextStream>//Biblioteca para Salvar e ler Strings dos arquivos

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

public slots:
    void attMsg();// funcao que atualiza as mensagens lidas

private:
    Ui::MainWindow *ui;
    QTimer *tempo;//variável para salvar o tempo lido
};

#endif // MAINWINDOW_H
