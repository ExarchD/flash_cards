#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "carding.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string question;
    std::vector<std::string> responses;
    flashes ThisCard;
    bool responded;
    int official_answer;

private slots:
    void on_answer1_clicked();

    void on_answer2_clicked();

    void on_answer3_clicked();

    void on_answer4_clicked();
    void Set_values(std::string, std::vector<std::string>);
    void run_check(int val);

    void on_skip_clicked();

    void on_continue_2_clicked();

public slots:
    void signal_recieved();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
