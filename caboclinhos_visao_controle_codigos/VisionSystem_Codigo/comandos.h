#ifndef COMANDOS_H
#define COMANDOS_H

#include <QWidget>

namespace Ui {
class Comandos;
}

class Comandos : public QWidget
{
    Q_OBJECT

public:
    explicit Comandos(QWidget *parent = 0);
    ~Comandos();
    int comando;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Comandos *ui;
};

#endif // COMANDOS_H
