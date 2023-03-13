#include "connectionwindow.h"
#include <qnamwrapper.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow w;
    QNAMwrapper qnamw;
    w.show();

    return a.exec();
}
