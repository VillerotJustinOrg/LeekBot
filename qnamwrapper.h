#ifndef QNAMWRAPPER_H
#define QNAMWRAPPER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>

class QNAMwrapper{
static QNetworkAccessManager* m_qnam;
public:
static QNetworkAccessManager* getQNAM() {
Q_ASSERT_X(m_qnam,"QNAMwrapper","You must create an instance of QNAMwrapper before using the QNAM");
return m_qnam;
}
QNAMwrapper(){
Q_ASSERT_X(!m_qnam,"QNAMwrapper","Only one instance of QNAMwrapper can be created");
    if(!m_qnam) {
        m_qnam=new QNetworkAccessManager;
        m_qnam->setCookieJar(new QNetworkCookieJar);
    }
}
~QNAMwrapper(){delete m_qnam; m_qnam=Q_NULLPTR;}
};

#endif // QNAMWRAPPER_H
