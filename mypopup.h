#ifndef MYPOPUP_H
#define MYPOPUP_H

#include <QDialog>

namespace Ui {
class MyPopUp;
}

class MyPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit MyPopUp(QWidget *parent = 0);
    ~MyPopUp();

signals:
    void signal_launch();

private slots:
    void on_restart_clicked();

    void on_exitbutton_clicked();

private:
    Ui::MyPopUp *ui;
};

#endif // MYPOPUP_H
