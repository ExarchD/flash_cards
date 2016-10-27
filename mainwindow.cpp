#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carding.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flashes ThisCard;
    ThisCard.card_init();
    ThisCard.get_next_flash(question, responses);
    Set_values(question,responses);
}

void MainWindow::Set_values(std::string question, std::vector<std::string> responses)
{
    ui->word_label->setText(QString::fromStdString(question));
    ui->answer1->setText(QString::fromStdString(responses[0]));
    ui->answer2->setText(QString::fromStdString(responses[1]));
    ui->answer3->setText(QString::fromStdString(responses[2]));
    ui->answer4->setText(QString::fromStdString(responses[3]));
}

MainWindow::~MainWindow()
{
    delete ui;
}
