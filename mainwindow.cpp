#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
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
    //QMessageBox::warning(this,"Token: ",this->userToken, "<br /> data: ", this->userdata);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: updateView() {
    ui->label->setText(this->userToken);
    ui->label_2->setText(this->userdata.toJson());
}
