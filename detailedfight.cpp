#include "detailedfight.h"
#include "ui_detailedfight.h"

DetailedFight::DetailedFight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailedFight)
{
    ui->setupUi(this);
}

DetailedFight::~DetailedFight()
{
    delete ui;
}
