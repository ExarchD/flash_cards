#include "mypopup.h"
#include "flash_alg.h"
#include "ui_mypopup.h"
#include <iostream>

MyPopUp::MyPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyPopUp)
{
    ui->setupUi(this);
}

MyPopUp::~MyPopUp()
{
    delete ui;
}

void MyPopUp::on_restart_clicked()
{
    /* flashes ThisCard; */
    /* ThisCard.exit_program(); */
    /* ThisCard.card_init(); */
    emit signal_launch();
    close();
}

void MyPopUp::on_exitbutton_clicked()
{
    exit (EXIT_SUCCESS);
}

