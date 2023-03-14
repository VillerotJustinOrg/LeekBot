#include "fightlist.h"
#include "ui_fightlist.h"


#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

FightList::FightList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FightList)
{
    ui->setupUi(this);
    setWindowTitle("Fights");
}

FightList::~FightList()
{
    delete ui;
}


void FightList:: on_pushButton_Ok_clicked(){
    qInfo() << "Ok clicked";
    this->close();
}

void FightList:: SetData(){
    qInfo() << "Set Data";
    foreach (int number, this->fightList) {
        QString temp(QString::number(number));
        this->CreateItem(ui->listWidget, temp);
    }
}

void FightList:: CreateItem (QListWidget * TheList , QString& TheText)
{
    qInfo() << "Create Item";
    QListWidgetItem * item = new QListWidgetItem ( "" );
    TheList->addItem ( item );
    // add a place hodler for label and button
    QWidget * w = new QWidget();
    w->setLayout ( new QHBoxLayout() );
    QPushButton *but = new QPushButton ( "More Info" );
    QLabel *lab = new QLabel ( TheText );
    // make row a bit bigger
    item->setSizeHint ( QSize ( item->sizeHint().width(), 30 ) );
    // add the label and button to the layout
    w->layout()->addWidget ( lab );
    w->layout()->addWidget ( but );
    // reduce the space around it abit
    w->layout()->setContentsMargins ( 1, 1, 1, 1 );
    // set this combined widget for the row
    TheList->setItemWidget ( item, w );

    QObject::connect(but, &QPushButton::clicked, [TheText, this](){
        this->fightDetail(TheText);
    });

    // https://leekwars.com/api/fight/get/ + id
}

void FightList:: fightDetail(QString idFight) {
    qInfo() << "More Info";
    qInfo() << idFight;
}

