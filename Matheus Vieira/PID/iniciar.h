#ifndef INICIAR_H
#define INICIAR_H

#include <QDialog>

namespace Ui {
class Iniciar;
}

class Iniciar : public QDialog
{
    Q_OBJECT

public:
    explicit Iniciar(QWidget *parent = nullptr);
    ~Iniciar();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Iniciar *ui;
};

#endif // INICIAR_H
