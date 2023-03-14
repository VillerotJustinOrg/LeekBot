#include "detailedfight.h"
#include "ui_detailedfight.h"

DetailedFight::DetailedFight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailedFight)
{
    ui->setupUi(this);
    setWindowTitle("LeekBot");
    this->setFixedSize(this->size());
}

DetailedFight::~DetailedFight()
{
    delete ui;
}

void DetailedFight:: SetData(){
    qInfo() << "Set Data";


}


/*
 * type int 0 = solo / 1 = farmer / 2 = Team
 * winner int 1 = win / 2 = lose / 3 or 0 = tie
 *
 * report = object
 *
 * in report -----------
 *
 * duration int
 *
 * leek1 {money int / name string / talent_gain int / xp int }
 *
 *
 * leek2
 *
 *
 * ----------------------
 *
 * team1_name
 * team2_name
 *
 * */
