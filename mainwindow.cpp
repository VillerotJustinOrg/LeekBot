#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("LeekBot");

    // Network stuff
    manager = new QNetworkAccessManager(this);
    manager->setCookieJar(new QNetworkCookieJar);

    // Set Button


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: updateView() {
    //////qInfo() << this->userdata.keys();
    //////qInfo() << this->userdata.keys();

    // set User Info
    this->userId = this->userdata.find("id").value().toInteger();

    ui->label_Username->setText(this->userdata.find("name").value().toString());
    //////qInfo() << this->userdata.find("name").value();

    QString temp = QString::number(this->userdata.find("fights").value().toInteger());
    //////qInfo() << this->userdata.find("fights").value();
    ui->label_Fights->setText(temp);

    temp = QString::number(this->userdata.find("talent").value().toInteger()) +"("+QString::number(this->userdata.find("talent_more").value().toInteger())+")";
    //////qInfo() << this->userdata.find("talent").value();
    ui->label_Talent->setText(temp);

    temp = QString::number(this->userdata.find("crystals").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    //////qInfo() << this->userdata.find("crystals").value();
    ui->label_Crystals->setText(temp);

    temp = QString::number(this->userdata.find("habs").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    //////qInfo() << this->userdata.find("habs").value();
    ui->label_Habs->setText(temp);

    // Avatar
    //https://leekwars.com/avatar/1.png

    // get teamID
    this->teamID = this->userdata.find("team")->toObject().find("id").value().toInteger();

    // get Team Object
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl url = QUrl("https://leekwars.com/api/team/get/"+QString::number(teamID));
    ////qInfo() << "https://leekwars.com/api/team/get/"+QString::number(teamID);
    QNetworkRequest request(url);
    ////qInfo() << "url & request done";
    QNetworkReply *rep = manager->get(request);
    eventLoop.exec();
    QByteArray jsonEquipe = rep->readAll();
    //QString str(jsonEquipe);
    ////qInfo() << "json get: ";
    ////qInfo() << str;
    this->team = new QJsonObject(QJsonDocument::fromJson(jsonEquipe).object());
    ////qInfo() << "json -> object done";

    // set Team info
    ////qInfo() << this->team->keys();
    ui->label_Team->setText(this->team->find("name").value().toString());
    ////qInfo() << "Team Name";

    temp = QString::number(this->team->find("talent").value().toInteger());
    ui->label_Talent_Team->setText(temp);
    ////qInfo() << "Team talent";

    temp = QString::number(this->team->find("level").value().toInteger());
    ui->label_Team_Level->setText(temp);
    ////qInfo() << "Team level";

    qint64 upXP = this->team->find("up_xp").value().toInteger();
    qint64 downXP = this->team->find("down_xp").value().toInteger();
    qint64 XP = this->team->find("xp").value().toInteger();

    ui->XP_progressBar->setMaximum(upXP);
    ui->XP_progressBar->setMinimum(downXP);
    ui->XP_progressBar->setValue(XP);


    // set Leeks Info
    // NB Leek leek_count
    this->NBLeek = this->userdata.find("leek_count").value().toInt();
    ui->label_NB_Leek->setText(QString::number(this->NBLeek));
    // Total Level Leek total_level
    ui->label_Total_Level_Leek->setText(QString::number(this->userdata.find("total_level").value().toInteger()));

    QJsonObject leeks = this->userdata.find("leeks")->toObject();
    int ct = 0;
    //qInfo() << "before loop";
    //qInfo() << leeks;
    foreach (QString leek, leeks.keys()) {
        //qInfo() << "In Loop";
        QEventLoop NeweventLoop;
        QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &NeweventLoop, SLOT(quit()));
        temp = QString::number(leeks.find(leek)->toObject().find("id")->toInteger());
        //qInfo() << leek;
        //qInfo() << temp;
        url = QUrl("https://leekwars.com/api/leek/get/"+temp);
        QNetworkRequest request(url);
        QNetworkReply *rep = manager->get(request);
        NeweventLoop.exec();
        QByteArray jsonLeek = rep->readAll();
        //qInfo() << jsonLeek;
        // Set Data Leek 1
        if (ct == 0) {
            this -> leek1 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());
            ui->label_Leek_Name->setText(this->leek1->find("name").value().toString());
            //qInfo() << this->leek1->find("name").value();
            //label_Leek_Name name
            temp = QString::number(this->leek1->find("talent").value().toInteger()) + "("+QString::number(this->leek1->find("talent_more").value().toInteger())+")" ;
            ui->label_Leek_Talent->setText(temp);
            //label_Leek_Talent talent talent_more
            ui->label_Leek_Level->setText(QString::number(this->leek1->find("level").value().toInteger()));
            //label_Leek_Level level
            upXP    = this->leek1->find("up_xp").value().toInteger();
            downXP  = this->leek1->find("down_xp").value().toInteger();
            XP      = this->leek1->find("xp").value().toInteger();

            ui->XP_progressBar_Leek->setMaximum(upXP);
            ui->XP_progressBar_Leek->setMinimum(downXP);
            ui->XP_progressBar_Leek->setValue(XP);
            //XP_progressBar_Leek xp down_xp up_xp
        }
        // Set Data Leek 2
        if (ct == 1) {
            this -> leek2 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());
            ui->label_Leek_Name_2->setText(this->leek2->find("name").value().toString());
            //qInfo() << this->leek2->find("name").value();
            //label_Leek_Name name
            temp = QString::number(this->leek2->find("talent").value().toInteger()) + "("+QString::number(this->leek2->find("talent_more").value().toInteger())+")" ;
            ui->label_Leek_Talent_2->setText(temp);
            //label_Leek_Talent talent talent_more
            ui->label_Leek_Level_2->setText(QString::number(this->leek2->find("level").value().toInteger()));
            //label_Leek_Level level
            upXP    = this->leek2->find("up_xp").value().toInteger();
            downXP  = this->leek2->find("down_xp").value().toInteger();
            XP      = this->leek2->find("xp").value().toInteger();

            ui->XP_progressBar_Leek_2->setMaximum(upXP);
            ui->XP_progressBar_Leek_2->setMinimum(downXP);
            ui->XP_progressBar_Leek_2->setValue(XP);
        }
        // Set Data Leek 3
        if (ct == 2) {
            this -> leek3 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());
            ui->label_Leek_Name_3->setText(this->leek3->find("name").value().toString());
            //qInfo() << this->leek3->find("name").value();
            //label_Leek_Name name
            temp = QString::number(this->leek3->find("talent").value().toInteger()) + "("+QString::number(this->leek3->find("talent_more").value().toInteger())+")" ;
            ui->label_Leek_Talent_3->setText(temp);
            //label_Leek_Talent talent talent_more
            ui->label_Leek_Level_3->setText(QString::number(this->leek3->find("level").value().toInteger()));
            //label_Leek_Level level
            upXP    = this->leek3->find("up_xp").value().toInteger();
            downXP  = this->leek3->find("down_xp").value().toInteger();
            XP      = this->leek3->find("xp").value().toInteger();

            ui->XP_progressBar_Leek_3->setMaximum(upXP);
            ui->XP_progressBar_Leek_3->setMinimum(downXP);
            ui->XP_progressBar_Leek_3->setValue(XP);
        }
        // Set Data Leek 4
        if (ct == 3) {
            this -> leek4 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());
            ui->label_Leek_Name_4->setText(this->leek4->find("name").value().toString());
            //qInfo() << this->leek4->find("name").value();
            //label_Leek_Name name
            temp = QString::number(this->leek4->find("talent").value().toInteger()) + "("+QString::number(this->leek4->find("talent_more").value().toInteger())+")" ;
            ui->label_Leek_Talent_4->setText(temp);
            //label_Leek_Talent talent talent_more
            ui->label_Leek_Level_4->setText(QString::number(this->leek4->find("level").value().toInteger()));
            //label_Leek_Level level
            upXP    = this->leek4->find("up_xp").value().toInteger();
            downXP  = this->leek4->find("down_xp").value().toInteger();
            XP      = this->leek4->find("xp").value().toInteger();

            ui->XP_progressBar_Leek_4->setMaximum(upXP);
            ui->XP_progressBar_Leek_4->setMinimum(downXP);
            ui->XP_progressBar_Leek_4->setValue(XP);
        }
        ct = ct+1;
    }

    // Set Fight Form

    // Leek ComboBox
    if(!this->leek1->isEmpty()){
        ui->comboBox_Fight_Leek->addItem(this->leek1->find("name").value().toString());
    }
    if(!this->leek2->isEmpty()){
        ui->comboBox_Fight_Leek->addItem(this->leek2->find("name").value().toString());
    }
    if(!this->leek3->isEmpty()){
        ui->comboBox_Fight_Leek->addItem(this->leek3->find("name").value().toString());
    }
    if(!this->leek4->isEmpty()){
        ui->comboBox_Fight_Leek->addItem(this->leek4->find("name").value().toString());
    }

    // Team ComboBox

}

void MainWindow:: on_pushButton_Start_Leek_Fight() {

    // Recover Form data

    // Which Leek


    // How many Fight



}
void MainWindow:: on_pushButton_Start_Farmer_Fight(){

}
void MainWindow:: on_pushButton_Start_Team_Fight(){

}
void MainWindow:: on_pushButton_Start_All_Farmer_Fight(){

}
void MainWindow:: on_pushButton_Start_All_Team_Fight(){

}
