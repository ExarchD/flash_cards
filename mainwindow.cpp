#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "mypopup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    TheseOptions.read_opts();
    ui->setupUi(this);
    ThisCard.card_init();
    ThisCard.get_next_flash(question, responses);
    Set_values(question,responses);
}

void MainWindow::Set_values(std::string question, std::vector<std::string> responses)
{
    responded=false;
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

void MainWindow::on_answer1_clicked()
{
    run_check(0);
}

void MainWindow::on_answer2_clicked()
{
    run_check(1);
}

void MainWindow::on_answer3_clicked()
{
    run_check(2);
}

void MainWindow::on_answer4_clicked()
{
    run_check(3);
}

void MainWindow::run_check(int val)
{
    ui->skip->setEnabled(false);
    if (!responded) {
        official_answer=val;
        responded=true;
    }
    int correct_val=ThisCard.check_answers(val);
    if (correct_val == val)
    {
        QPalette palette_sample;
        palette_sample.setColor(QPalette::Button, Qt::green);
        if (val == 0) ui->answer1->setPalette(palette_sample);
        if (val == 1) ui->answer2->setPalette(palette_sample);
        if (val == 2) ui->answer3->setPalette(palette_sample);
        if (val == 3) ui->answer4->setPalette(palette_sample);
    }
    else
    {
        QPalette palette_sample;
        palette_sample.setColor(QPalette::Button, Qt::red);
        if (val == 0) ui->answer1->setPalette(palette_sample);
        if (val == 1) ui->answer2->setPalette(palette_sample);
        if (val == 2) ui->answer3->setPalette(palette_sample);
        if (val == 3) ui->answer4->setPalette(palette_sample);
    }
}

void MainWindow::on_skip_clicked()
{
    ThisCard.process_response(999);
    ThisCard.get_next_flash(question, responses);
    Set_values(question,responses);
}


/* popup::popup(QWidget *parent) : */
/*     QDialog(parent), */
/*     ui(new Ui::popup) */
/* { */
/*     ui->setupUi(this); */
/* } */

/* popup::~popup() */
/* { */
/*     delete ui; */
/* } */
void MainWindow::on_continue_2_clicked()
{
    ThisCard.process_response(official_answer);
    ThisCard.get_next_flash(question, responses);
    if ( responses.size() < 2 )
    {
        ThisCard.exit_program();
        MyPopUp *Thispop= new MyPopUp(this);
        Thispop->show();
        connect(Thispop, SIGNAL(signal_launch()), this, SLOT(signal_recieved()));
    }
    else
    {
        Set_values(question,responses);
    }
    QPalette palette_sample;
    ui->answer1->setPalette(ui->answer1->style()->standardPalette());
    ui->answer2->setPalette(ui->answer2->style()->standardPalette());
    ui->answer3->setPalette(ui->answer3->style()->standardPalette());
    ui->answer4->setPalette(ui->answer4->style()->standardPalette());
    ui->skip->setEnabled(true);
    responded=false;
}

void MainWindow::signal_recieved()
{
    ThisCard.card_init();
    ThisCard.get_next_flash(question, responses);
    Set_values(question,responses);
}
