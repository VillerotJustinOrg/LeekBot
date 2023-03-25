QT       += core gui network widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connectionwindow.cpp \
    detailedfight.cpp \
    fightlist.cpp \
    main.cpp \
    mainwindow.cpp \
    qnamwrapper.cpp

HEADERS += \
    connectionwindow.h \
    detailedfight.h \
    fightlist.h \
    mainwindow.h \
    qnamwrapper.h

FORMS += \
    connectionwindow.ui \
    detailedfight.ui \
    fightlist.ui \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
