#ifndef REGISTRATHION_H
#define REGISTRATHION_H

#include <QWidget>

namespace Ui {
class registrathion;
}

class registrathion : public QWidget
{
    Q_OBJECT

public:
    explicit registrathion(QWidget *parent = nullptr);
    ~registrathion();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::registrathion *ui;
};

#endif // REGISTRATHION_H
