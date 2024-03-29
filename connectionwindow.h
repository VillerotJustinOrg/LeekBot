#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();

private slots:
    //      pushButton_Login
    void on_pushButton_Login_clicked();
    void messageErreur(QNetworkReply::NetworkError);

private:
    Ui::ConnectionWindow *ui;
    MainWindow *mainwindow;
    QUrl url;
};

#endif // CONNECTIONWINDOW_H
