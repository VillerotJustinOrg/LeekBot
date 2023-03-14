#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkCookie>
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
    Q_OBJECT;
public slots:
    void SetData();

private slots:
    void updateView();
    void on_pushButton_All_Farmer_clicked();
    void on_pushButton_All_Team_clicked();
    void on_pushButton_Fight_Farmer_clicked();
    void on_pushButton_Fight_Leek_clicked();
    void on_pushButton_Fight_Team_clicked();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJsonObject userdata;

private:
    Ui::MainWindow *ui;
    qint64 userId;
    qint64 teamID;
    QJsonObject *team;
    QJsonObject *leek1;
    QJsonObject *leek2;
    QJsonObject *leek3;
    QJsonObject *leek4;
    QList<int> teams;
    int NBLeek;
};

#endif // MAINWINDOW_H
