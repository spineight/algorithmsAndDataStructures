#include "progressdialog.h"
#include "ui_progressdialog.h"


ProgressDialog::ProgressDialog(QThread* searchThread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog),
    searchThread(searchThread)
{
    ui->setupUi(this);
    connect(ui->stopSearchButton, SIGNAL(clicked()), this, SLOT(stopSearch()));
    ui->progressBar->setValue(0);
    ui->label->setText("Scaning directory..");
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::setRange(int max){
    ui->progressBar->setRange(0,max);
    amount = max;
}
void ProgressDialog::stopSearch() {
    this->done(0);
    searchThread->requestInterruption();
}

void ProgressDialog::update() {
    ui->label->setText(QString::number(++num) + " / " + QString::number(amount) +" have already indexed");
    ui->progressBar->setValue(num);
}
