#include "detailedfight.h"
#include "ui_detailedfight.h"
#include <qnamwrapper.h>
// Misc Inport
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
// Network Inport
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkCookie>
#include <QUrl>
// Json Inport
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

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

    // Get Fight Repport

    QEventLoop eventLoop;
    QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QUrl url = QUrl("https://leekwars.com/api/fight/get/"+this->fightId);
    //qInfo() << url;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
    eventLoop.exec();
    QByteArray jsonReport = rep->readAll();
    QJsonObject Repport = QJsonDocument::fromJson(jsonReport).object();

    qInfo() << "Repport Get";

    // set Name

    ui->label_Username->setText(Repport.find("team1_name").value().toString());
    ui->label_Enemyname->setText(Repport.find("team2_name").value().toString());
    qInfo() << "Name Set";

    // Set Type of fight

    switch (Repport.find("type").value().toInt()) {
    case 1:
        ui->label_Type->setText("Farmer Fight");
        break;
    case 2:
        ui->label_Type->setText("Team Fight");
        break;
    default:
        ui->label_Type->setText("Solo Fight");
        break;
    }
    qInfo() << "Type Set";

    // Set Winer

    switch (Repport.find("winner").value().toInt()) {
    case 1:
        ui->label_User_Win->setText("WIN");
        ui->label_Enemy_Win->setText("LOSE");
        break;
    case 2:
        ui->label_User_Win->setText("LOSE");
        ui->label_Enemy_Win->setText("WIN");
        break;
    default:
        ui->label_User_Win->setText("TIE");
        ui->label_Enemy_Win->setText("TIE");
        break;
    }
    qInfo() << "Winner Set";

    // Set Tab data

    QJsonObject RepportData = Repport.find("report").value().toObject();
    QJsonArray Group1 = RepportData.find("leeks1")->toArray();
    QJsonArray Group2 = RepportData.find("leeks2")->toArray();
    qInfo() << "Get Group";

    if (Repport.find("type").value().toInt() != 0){
        ui->tableWidget_Enemy->removeColumn(5);
        ui->tableWidget_User->removeColumn(5);
    }

    foreach (QJsonValueConstRef leek, Group1) {
        QJsonObject leekOBJ = leek.toObject();
        // create row
        ui->tableWidget_User->insertRow(ui->tableWidget_User->rowCount());

        // create items
        QTableWidgetItem *leekName = new QTableWidgetItem();
        QTableWidgetItem *leekLevel = new QTableWidgetItem();
        QTableWidgetItem *leekXP = new QTableWidgetItem();
        QTableWidgetItem *leekMoney = new QTableWidgetItem();
        QTableWidgetItem *leekTalent = new QTableWidgetItem();
        QTableWidgetItem *leekDead = new QTableWidgetItem();

        // set Item Value
        leekName->setText(leekOBJ.find("name").value().toString());
        leekLevel->setText(QString::number(leekOBJ.find("level").value().toInt()));
        leekXP->setText(QString::number(leekOBJ.find("xp").value().toInt()));
        leekMoney->setText(QString::number(leekOBJ.find("money").value().toInt()));
        if (Repport.find("type").value().toInt() != 0) {
            leekTalent->setText(QString::number(leekOBJ.find("talent_gain").value().toInt()));
        }
        leekDead->setText(QString::number(leekOBJ.find("dead").value().toBool()));

        // set items
        ui->tableWidget_User->setItem(ui->tableWidget_User->rowCount()-1, 0, leekName);
        ui->tableWidget_User->setItem(ui->tableWidget_User->rowCount()-1, 1, leekLevel);
        ui->tableWidget_User->setItem(ui->tableWidget_User->rowCount()-1, 2, leekXP);
        ui->tableWidget_User->setItem(ui->tableWidget_User->rowCount()-1, 3, leekMoney);
        ui->tableWidget_User->setItem(ui->tableWidget_User->rowCount()-1, 4, leekDead);
        if (Repport.find("type").value().toInt() != 0) {
            ui->tableWidget_User->setItem(ui->tableWidget_Enemy->rowCount()-1, 5, leekTalent);
        }


    }

    qInfo() << "Group1 set";

    foreach (QJsonValueConstRef leek, Group2) {
        QJsonObject leekOBJ = leek.toObject();
        ui->tableWidget_Enemy->insertRow(ui->tableWidget_Enemy->rowCount());
        // create items
        QTableWidgetItem *leekName = new QTableWidgetItem();
        QTableWidgetItem *leekLevel = new QTableWidgetItem();
        QTableWidgetItem *leekXP = new QTableWidgetItem();
        QTableWidgetItem *leekMoney = new QTableWidgetItem();
        QTableWidgetItem *leekTalent = new QTableWidgetItem();
        QTableWidgetItem *leekDead = new QTableWidgetItem();

        // set Item Value
        leekName->setText(leekOBJ.find("name").value().toString());
        leekLevel->setText(QString::number(leekOBJ.find("level").value().toInt()));
        leekXP->setText(QString::number(leekOBJ.find("xp").value().toInt()));
        leekMoney->setText(QString::number(leekOBJ.find("money").value().toInt()));
        if (Repport.find("type").value().toInt() != 0) {
            leekTalent->setText(QString::number(leekOBJ.find("talent_gain").value().toInt()));
        }
        leekDead->setText(QString::number(leekOBJ.find("dead").value().toBool()));

        // set items
        ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 0, leekName);
        ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 1, leekLevel);
        ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 2, leekXP);
        ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 3, leekMoney);
        ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 4, leekDead);
        if (Repport.find("type").value().toInt() != 0) {
            ui->tableWidget_Enemy->setItem(ui->tableWidget_Enemy->rowCount()-1, 5, leekTalent);
        }
    }

    qInfo() << "Group2 set";


    // Set Team / Farmer Spécial data
    if (Repport.find("type").value().toInt() == 2){
        // Team Talent
        ui->label_O_T_U->setText(QString::number(RepportData.find("team1")->toObject().find("talent_gain").value().toInt()));
        ui->label_O_T_E->setText(QString::number(RepportData.find("team2")->toObject().find("talent_gain").value().toInt()));
        // Team XP
        ui->label_O_X_U->setText(QString::number(RepportData.find("team1")->toObject().find("xp").value().toInt()));
        ui->label_O_X_E->setText(QString::number(RepportData.find("team2")->toObject().find("xp").value().toInt()));
    }
    qInfo() << "Team data set";

    if (Repport.find("type").value().toInt() == 1){
        // Farmer Talent
        ui->label_O_T_U->setText(QString::number(RepportData.find("farmer1")->toObject().find("talent_gain").value().toInt()));
        ui->label_O_T_E->setText(QString::number(RepportData.find("farmer2")->toObject().find("talent_gain").value().toInt()));
    }
    qInfo() << "Farmer data set";


    // Set Label Link

    ui->label_Link->setText("<a href=\"https://leekwars.com/report/"+this->fightId+">Full Repport</a>");

    qInfo() << "Link set";
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
