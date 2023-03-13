#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
public slots:
    void updateView();

private slots:
    void on_pushButton_Start_Leek_Fight();
    void on_pushButton_Start_Farmer_Fight();
    void on_pushButton_Start_Team_Fight();
    void on_pushButton_Start_All_Farmer_Fight();
    void on_pushButton_Start_All_Team_Fight();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJsonObject userdata;
    QString userToken;

private:
    Ui::MainWindow *ui;
    qint64 userId;
    qint64 teamID;
    QJsonObject *team;
    QNetworkAccessManager *manager;
    QJsonObject *leek1;
    QJsonObject *leek2;
    QJsonObject *leek3;
    QJsonObject *leek4;
    int NBLeek;
};

#endif // MAINWINDOW_H
