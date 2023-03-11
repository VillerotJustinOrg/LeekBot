#include "connectionwindow.h"
#include "ui_connectionwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>


ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{

    // UI Stuff
    ui->setupUi(this);
    setWindowTitle("LeekBot");
    QPixmap pix(":/resources/images/leekwars.svg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::on_pushButton_Login_clicked()
{
    // form data

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // Request
    const QUrl url = QUrl("https://leekwars.com/api/farmer/login");                             // set url
    QNetworkRequest request(url);                                                               // On crée notre requête
    QString donnees = "login=" + username + "&password=" + password + "&keep_connected=true";     // set Data
    request.setRawHeader("content-type", "application/x-www-form-urlencoded; charset=UTF-8");                     // set Header
    QNetworkAccessManager *m = new QNetworkAccessManager(this);               // Network Manager

    // do things depending request result
    connect(m, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
    connect(m, SIGNAL(finished(QNetworkReply*)), this, SLOT(fin(QNetworkReply*)));

    m->post(request, donnees.toLatin1()); // post Request
}

void ConnectionWindow::fin(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();
    QString str(bts);

    // Show result

    bool request_result = false;
    if(str != "{\"error\":\"invalid\"}") {
        request_result = true;
    }
    //QMessageBox::information(this, "Fin de post", "L'envoi de données par POST a été effectué avec succès ! Result; <br /><em>" + str + "</em>");


    if (request_result) {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        mainwindow = new MainWindow(this);
        mainwindow->show();
        mainwindow->userdata = str;
        mainwindow->userToken = "str1324684513";
        mainwindow->updateView();
    }
    else {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}

void ConnectionWindow::messageErreur(QNetworkReply::NetworkError)
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, "Erreur", "Erreur lors de la connection. <br /><br /> Code de l'erreur : <br /><em>" + r->errorString() + "</em>");
    //close();
}
