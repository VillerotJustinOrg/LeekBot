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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: updateView() {
    ////qInfo() << this->userdata.keys();
    ////qInfo() << this->userdata.keys();

    // set User Info
    this->userId = this->userdata.find("id").value().toInteger();

    ui->label_Username->setText(this->userdata.find("name").value().toString());
    ////qInfo() << this->userdata.find("name").value();

    QString temp = QString::number(this->userdata.find("fights").value().toInteger());
    ////qInfo() << this->userdata.find("fights").value();
    ui->label_Fights->setText(temp);

    temp = QString::number(this->userdata.find("talent").value().toInteger());
    ////qInfo() << this->userdata.find("talent").value();
    ui->label_Talent->setText(temp);

    temp = QString::number(this->userdata.find("crystals").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    ////qInfo() << this->userdata.find("crystals").value();
    ui->label_Crystals->setText(temp);

    temp = QString::number(this->userdata.find("habs").value().toInteger());
    for(int i=temp.length()-3;i>0;i-=3)
        temp.insert(i,' ');
    ////qInfo() << this->userdata.find("habs").value();
    ui->label_Habs->setText(temp);

    // Avatar
    //https://leekwars.com/avatar/1.png

    // get teamID
    this->teamID = this->userdata.find("team")->toObject().find("id").value().toInteger();

    // get Team Object
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl url = QUrl("https://leekwars.com/api/team/get/"+QString::number(teamID));
    //qInfo() << "https://leekwars.com/api/team/get/"+QString::number(teamID);
    QNetworkRequest request(url);
    //qInfo() << "url & request done";
    QNetworkReply *rep = manager->get(request);
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

    // get team required for more info
    // https://leekwars.com/api/team/get/idTeam


    // set Leeks Info


    //total_level
    // leek_count

}
