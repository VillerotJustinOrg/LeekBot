#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("LeekBot");
    this->setFixedSize(this->size());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: SetData() {

    // set User Info
    this->userId = this->userdata.find("id").value().toInteger();

    ui->label_Username->setText(this->userdata.find("name").value().toString());
    //qInfo() << this->userdata.find("name").value();

    QString temp = QString::number(this->userdata.find("fights").value().toInteger());
    //qInfo() << this->userdata.find("fights").value();
    ui->label_Fights->setText(temp);

    temp = QString::number(this->userdata.find("talent").value().toInteger()) +"("+QString::number(this->userdata.find("talent_more").value().toInteger())+")";
    //qInfo() << this->userdata.find("talent").value();
    ui->label_Talent->setText(temp);

    temp = QString::number(this->userdata.find("crystals").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    //qInfo() << this->userdata.find("crystals").value();
    ui->label_Crystals->setText(temp);

    temp = QString::number(this->userdata.find("habs").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    //qInfo() << this->userdata.find("habs").value();
    ui->label_Habs->setText(temp);

   //qInfo() << "Update View - User";

    // Form
    ui->spinBox_Fight_Leek->setMinimum(0);
    ui->spinBox_Fight_Leek->setMaximum(this->userdata.find("fights").value().toInt());
    ui->spinBox_Fight_Farmer->setMinimum(0);
    ui->spinBox_Fight_Farmer->setMaximum(this->userdata.find("fights").value().toInt());

    // Avatar
    //https://leekwars.com/avatar/1.png
   //qInfo() << "Update View - Form1";

    // get teamID
    this->teamID = this->userdata.find("team")->toObject().find("id").value().toInteger();

    // get Team Object
    QEventLoop eventLoop;
    QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl url = QUrl("https://leekwars.com/api/team/get/"+QString::number(teamID));
    ////qInfo() << "https://leekwars.com/api/team/get/"+QString::number(teamID);
    QNetworkRequest request(url);
    ////qInfo() << "url & request done";
    QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
    eventLoop.exec();
    QByteArray jsonEquipe = rep->readAll();
    //QString str(jsonEquipe);
    //qInfo() << "json get: ";
    //qInfo() << str;
    this->team = new QJsonObject(QJsonDocument::fromJson(jsonEquipe).object());
    //qInfo() << "json -> object done";

    // set Team info
    //qInfo() << this->team->keys();
    ui->label_Team->setText(this->team->find("name").value().toString());
    //qInfo() << "Team Name";

    temp = QString::number(this->team->find("talent").value().toInteger());
    ui->label_Talent_Team->setText(temp);
    //qInfo() << "Team talent";

    temp = QString::number(this->team->find("level").value().toInteger());
    ui->label_Team_Level->setText(temp);
    //qInfo() << "Team level";

    qint64 upXP = this->team->find("up_xp").value().toInteger();
    qint64 downXP = this->team->find("down_xp").value().toInteger();
    qint64 XP = this->team->find("xp").value().toInteger();

    ui->XP_progressBar->setMaximum(upXP);
    ui->XP_progressBar->setMinimum(downXP);
    ui->XP_progressBar->setValue(XP);

   //qInfo() << "Update View - Team";

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
        QEventLoop eventLoop;
        QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        temp = QString::number(leeks.find(leek)->toObject().find("id")->toInteger());
        //qInfo() << leek;
        //qInfo() << temp;
        url = QUrl("https://leekwars.com/api/leek/get/"+temp);
        QNetworkRequest request(url);
        QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
        eventLoop.exec();
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
            ui->comboBox_Fight_Leek->addItem(this->leek1->find("name").value().toString());
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

            ui->comboBox_Fight_Leek->addItem(this->leek2->find("name").value().toString());
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

            ui->comboBox_Fight_Leek->addItem(this->leek3->find("name").value().toString());
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

            ui->comboBox_Fight_Leek->addItem(this->leek4->find("name").value().toString());
        }
        ct = ct+1;
    }
   //qInfo() << "Update View - Leek";

    // Team ComboBox

   //qInfo() << "Update View - Form2";
}

//==========================================================================================================

void MainWindow:: updateView() {
    qInfo() << "Update View";

    QString temp;

    // Get New User https://leekwars.com/api/farmer/get/43024

    QEventLoop eventLoop;
    QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl url = QUrl("https://leekwars.com/api/farmer/get/"+QString::number(this->userId));
    qInfo() << "https://leekwars.com/api/team/get/"+QString::number(teamID);
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    qInfo() << "url & request done";
    QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
    eventLoop.exec();
    QByteArray jsonFarmer = rep->readAll();
    qInfo() << jsonFarmer;
    if (jsonFarmer.isEmpty()  || jsonFarmer == "Too Many Requests") {
        QMessageBox::information(this, "UserData", "Error - Not found");
        return;
    }
    this->userdata = QJsonObject(QJsonDocument::fromJson(jsonFarmer).object().find("farmer")->toObject());
    qInfo() << "User get";


    temp = QString::number(this->userdata.find("fights").value().toInteger());
    //qInfo() << this->userdata.find("fights").value();
    ui->label_Fights->setText(temp);

    temp = QString::number(this->userdata.find("talent").value().toInteger()) +"("+QString::number(this->userdata.find("talent_more").value().toInteger())+")";
    //qInfo() << this->userdata.find("talent").value();
    ui->label_Talent->setText(temp);

    /* Need An other get
    temp = QString::number(this->userdata.find("crystals").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    //qInfo() << this->userdata.find("crystals").value();
    ui->label_Crystals->setText(temp);

    temp = QString::number(this->userdata.find("habs").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    qInfo() << this->userdata.find("habs").value();
    ui->label_Habs->setText(temp);
    */

    ui->spinBox_Fight_Leek->setMaximum(this->userdata.find("fights").value().toInt());
    ui->spinBox_Fight_Farmer->setMaximum(this->userdata.find("fights").value().toInt());

    qInfo() << "User Finished";

    // Get Team

    QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    url = QUrl("https://leekwars.com/api/team/get/"+QString::number(teamID));
    ////qInfo() << "https://leekwars.com/api/team/get/"+QString::number(teamID);
    request = QNetworkRequest(QUrl(url));
    ////qInfo() << "url & request done";
    rep = QNAMwrapper::getQNAM()->get(request);
    eventLoop.exec();
    QByteArray jsonEquipe = rep->readAll();
    //QString str(jsonEquipe);
    //qInfo() << "json get: ";
    //qInfo() << str;
    this->team = new QJsonObject(QJsonDocument::fromJson(jsonEquipe).object());

    if (this->team->empty() || jsonEquipe == "Too Many Requests") {
        QMessageBox::information(this, "Team Data", "Error - Not found");
        return;
    }
    //qInfo() << "json -> object done";

    temp = QString::number(this->team->find("talent").value().toInteger());
    ui->label_Talent_Team->setText(temp);
    //qInfo() << "Team talent";

    temp = QString::number(this->team->find("level").value().toInteger());
    ui->label_Team_Level->setText(temp);
    //qInfo() << "Team level";

    qint64 upXP = this->team->find("up_xp").value().toInteger();
    qint64 downXP = this->team->find("down_xp").value().toInteger();
    qint64 XP = this->team->find("xp").value().toInteger();

    ui->XP_progressBar->setMaximum(upXP);
    ui->XP_progressBar->setMinimum(downXP);
    ui->XP_progressBar->setValue(XP);

   //qInfo() << "Update View - Team";

    qInfo() << "TeamFinished";
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
        QEventLoop eventLoop;
        QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        temp = QString::number(leeks.find(leek)->toObject().find("id")->toInteger());
        //qInfo() << leek;
        //qInfo() << temp;
        url = QUrl("https://leekwars.com/api/leek/get/"+temp);
        QNetworkRequest request(url);
        QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
        eventLoop.exec();
        QByteArray jsonLeek = rep->readAll();
        qInfo() << jsonLeek;
        if (jsonLeek.isEmpty() || jsonLeek == "Too Many Requests") {
            QMessageBox::information(this, "Leek Data", "Error - Not found");
            return;
        }
        //qInfo() << jsonLeek;
        // Set Data Leek 1
        if (ct == 0) {
            this -> leek1 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());


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
            ui->comboBox_Fight_Leek->addItem(this->leek1->find("name").value().toString());
        }
        // Set Data Leek 2
        if (ct == 1) {
            this -> leek2 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());

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

            ui->comboBox_Fight_Leek->addItem(this->leek2->find("name").value().toString());
        }
        // Set Data Leek 3
        if (ct == 2) {
            this -> leek3 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());

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

            ui->comboBox_Fight_Leek->addItem(this->leek3->find("name").value().toString());
        }
        // Set Data Leek 4
        if (ct == 3) {
            this -> leek4 = new QJsonObject(QJsonDocument::fromJson(jsonLeek).object());

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

            ui->comboBox_Fight_Leek->addItem(this->leek4->find("name").value().toString());
        }
        ct = ct+1;
    }

    qInfo() << "Leek Finished";


}

// ====================================================================================================================

void MainWindow:: on_pushButton_Fight_Leek_clicked() {
   //qInfo() << "Leek Fight";

    // get data from form
    int selectedLeek = ui->comboBox_Fight_Leek->currentIndex();
    int numberOfFight = ui->spinBox_Fight_Leek->value();
   //qInfo() << selectedLeek;
   //qInfo() << numberOfFight;
    // Get Leek Id
    int LeekId;
    switch (selectedLeek) {
    default:
        LeekId = this->leek1->find("id")->toInt();
        break;
    case 1:
        LeekId = this->leek2->find("id")->toInt();
        break;
    case 2:
        LeekId = this->leek3->find("id")->toInt();
        break;
    case 3:
        LeekId = this->leek4->find("id")->toInt();
        break;
    }
   //qInfo() << LeekId;

    for (int i = 0; i < numberOfFight; ++i) {
        qInfo() << "Fight Begin";
        // get Opponents https://leekwars.com/api/garden/get-leek-opponents/46920
        QEventLoop eventLoop;
        QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QUrl url = QUrl("https://leekwars.com/api/garden/get-leek-opponents/"+QString::number(LeekId));
        qInfo() << url;
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
        eventLoop.exec();
        QByteArray jsonOpponent = rep->readAll();
        qInfo() << jsonOpponent;
        // get first opponent
        QJsonArray opponents = QJsonDocument::fromJson(jsonOpponent).object().find(QJsonDocument::fromJson(jsonOpponent).object().keys().at(0))->toArray();

        if (opponents.empty() || jsonOpponent == "Too Many Requests") {
            QMessageBox::information(this, "Fight", "Error");
            return;
        }

        qInfo() << opponents;
        qInfo() << opponents.at(0);
        // Get first Opponent If
        QJsonObject opponent = opponents[0].toObject();
        qInfo() << "first op";
        int OpponentId = opponent.find("id")->toInt();
        qInfo() << "OP ID: " + QString::number(OpponentId);


        // Fight https://leekwars.com/api/garden/start-solo-fight

        url = QUrl("https://leekwars.com/api/garden/start-solo-fight");
        qInfo() << url;
        request = QNetworkRequest(QUrl(url));
        // set Header
        request.setRawHeader("content-type", "application/x-www-form-urlencoded; charset=UTF-8");
        request.setRawHeader("user-agent", "Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0");
        request.setRawHeader("chost", "leekwars.com");
        request.setRawHeader("accept", "*/*");
        request.setRawHeader("origin", "https://leekwars.com");
        request.setRawHeader("sec-fetch-dest", "empty");
        request.setRawHeader("sec-fetch-mode", "cors");
        request.setRawHeader("sec-fetch-site", "same-origin");
        //request.setRawHeader("referer", "https://leekwars.com/api/garden/start-solo-fight");

        QString data = "leek_id=" + QString::number(LeekId) + "&target_id=" + QString::number(OpponentId);      // set Data
        qInfo() << "before request post";
        rep = QNAMwrapper::getQNAM()->post(request, data.toLatin1());
        eventLoop.exec();
        qInfo() << "after request post";
        // Result

        QByteArray jsonFight = rep->readAll();
        qInfo() << jsonFight;
        int fightId = QJsonDocument::fromJson(jsonFight).object().find("fight")->toInt();
        qInfo() << fightId;

        // Show Result in other window


        qInfo() << "Fight Stop";
    }
    // Update page
    this->updateView();

}


void MainWindow:: on_pushButton_Fight_Farmer_clicked() {
    qInfo() << "Farmer Fight";

    // get data from form
    int numberOfFight = ui->spinBox_Fight_Farmer->value();
    qInfo() << numberOfFight;

    for (int i = 0; i < numberOfFight; ++i) {
        qInfo() << "Fight Begin";

        // get Opponents https://leekwars.com/api/garden/get-farmer-opponents
        QEventLoop eventLoop;
        QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QUrl url = QUrl("https://leekwars.com/api/garden/get-farmer-opponents");
        qInfo() << url;
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
        eventLoop.exec();
        QByteArray jsonOpponent = rep->readAll();
        qInfo() << jsonOpponent;
        // get first opponent
        QJsonArray opponents = QJsonDocument::fromJson(jsonOpponent).object().find(QJsonDocument::fromJson(jsonOpponent).object().keys().at(0))->toArray();
          if (opponents.empty() || jsonOpponent == "Too Many Requests") {
            QMessageBox::information(this, "Fight", "Error");
            return;
        }
        qInfo() << opponents;
        qInfo() << opponents.at(0);
        // Get first Opponent If
        QJsonObject opponent = opponents[0].toObject();
        qInfo() << "first op";
        int OpponentId = opponent.find("id")->toInt();
        qInfo() << "OP ID: " + QString::number(OpponentId);

        // Fight https://leekwars.com/api/garden/start-farmer-fight
        url = QUrl("https://leekwars.com/api/garden/start-farmer-fight");
        qInfo() << url;
        request = QNetworkRequest(QUrl(url));
        // set Header
        request.setRawHeader("content-type", "application/x-www-form-urlencoded; charset=UTF-8");
        request.setRawHeader("user-agent", "Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0");
        request.setRawHeader("chost", "leekwars.com");
        request.setRawHeader("accept", "*/*");
        request.setRawHeader("origin", "https://leekwars.com");
        request.setRawHeader("sec-fetch-dest", "empty");
        request.setRawHeader("sec-fetch-mode", "cors");
        request.setRawHeader("sec-fetch-site", "same-origin");
        //request.setRawHeader("referer", "https://leekwars.com/api/garden/start-solo-fight");
        QString data = "target_id=" + QString::number(OpponentId);      // set Data
        qInfo() << "before request post";
        rep = QNAMwrapper::getQNAM()->post(request, data.toLatin1());
        eventLoop.exec();
        qInfo() << "after request post";
        // Result
        QByteArray jsonFight = rep->readAll();
        qInfo() << jsonFight;
        int fightId = QJsonDocument::fromJson(jsonFight).object().find("fight")->toInt();
        qInfo() << fightId;
        // Show Result in other window

        qInfo() << "Fight Stop";
    }

    // Update page
    this->updateView();

}



void MainWindow:: on_pushButton_Fight_Team_clicked() {
    qInfo() << "Team Fight";

    if (ui->comboBox_Fight_Team->count() < 1){
        QMessageBox::information(this, "Fight", "Error No team");
        return;
    }

    // get data from form
    int selectedTeam = ui->comboBox_Fight_Team->currentIndex();
    int numberOfFight = ui->spinBox_Fight_Team->value();

    qInfo() << numberOfFight;

    int TeamId = this->teams.at(selectedTeam);


    for (int i = 0; i < numberOfFight; ++i) {
        qInfo() << "Fight Begin";

        // get Opponents https://leekwars.com/api/garden/get-composition-opponents/
        QEventLoop eventLoop;
        QObject::connect(QNAMwrapper::getQNAM(), SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QUrl url = QUrl("https://leekwars.com/api/garden/get-composition-opponents/"+QString::number(TeamId));
        qInfo() << url;
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        QNetworkReply *rep = QNAMwrapper::getQNAM()->get(request);
        eventLoop.exec();
        QByteArray jsonOpponent = rep->readAll();
        qInfo() << jsonOpponent;
        // get first opponent
        QJsonArray opponents = QJsonDocument::fromJson(jsonOpponent).object().find(QJsonDocument::fromJson(jsonOpponent).object().keys().at(0))->toArray();
          if (opponents.empty() || jsonOpponent == "Too Many Requests") {
            QMessageBox::information(this, "Fight", "Error");
            return;
        }
        qInfo() << opponents;
        qInfo() << opponents.at(0);
        // Get first Opponent If
        QJsonObject opponent = opponents[0].toObject();
        qInfo() << "first op";
        int OpponentId = opponent.find("id")->toInt();
        qInfo() << "OP ID: " + QString::number(OpponentId);

        // Fight https://leekwars.com/api/garden/start-farmer-fight
        url = QUrl("https://leekwars.com/api/garden/start-team-fight");
        qInfo() << url;
        request = QNetworkRequest(QUrl(url));
        // set Header
        request.setRawHeader("content-type", "application/x-www-form-urlencoded; charset=UTF-8");
        request.setRawHeader("user-agent", "Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0");
        request.setRawHeader("chost", "leekwars.com");
        request.setRawHeader("accept", "*/*");
        request.setRawHeader("origin", "https://leekwars.com");
        request.setRawHeader("sec-fetch-dest", "empty");
        request.setRawHeader("sec-fetch-mode", "cors");
        request.setRawHeader("sec-fetch-site", "same-origin");
        //request.setRawHeader("referer", "https://leekwars.com/api/garden/start-solo-fight");
        QString data = "composition_id="+QString::number(TeamId)+"&target_id=" + QString::number(OpponentId);      // set Data
        qInfo() << "before request post";
        rep = QNAMwrapper::getQNAM()->post(request, data.toLatin1());
        eventLoop.exec();
        qInfo() << "after request post";
        // Result
        QByteArray jsonFight = rep->readAll();
        qInfo() << jsonFight;
        int fightId = QJsonDocument::fromJson(jsonFight).object().find("fight")->toInt();
        qInfo() << fightId;
        // Show Result in other window

        qInfo() << "Fight Stop";
    }

    // Update page
    this->updateView();
}

void MainWindow:: on_pushButton_All_Farmer_clicked() {
   //qInfo() << "All Farmer";
}

void MainWindow:: on_pushButton_All_Team_clicked() {
   //qInfo() << "All Team";
}
