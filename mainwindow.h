#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
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


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJsonDocument userdata;
    QString userToken;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
