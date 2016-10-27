#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carding.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flashes ThisCard;
    /* ThisCard.card_main(); */
}

MainWindow::~MainWindow()
{
    delete ui;
}
