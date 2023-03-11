#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QMainWindow>
#include "secdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void TestConnection() const;
    static void ReplyFinished(QNetworkReply *reply);
    QNetworkAccessManager *manager;

private slots:
    void on_pushButton_Login_clicked();
    void fin(QNetworkReply*);
    void messageErreur(QNetworkReply::NetworkError);

private:
    Ui::MainWindow *ui;
    SecDialog *secDialog;
};

#endif // MAINWINDOW_H
