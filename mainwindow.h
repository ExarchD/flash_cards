#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>

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
    void Set_values(std::string, std::vector<std::string>);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
