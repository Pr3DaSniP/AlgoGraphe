QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arbre.cpp \
    Graphe.cpp \
    GrapheNonOriente.cpp \
    GrapheNonOrienteValue.cpp \
    GrapheOriente.cpp \
    GrapheOrienteValue.cpp \
    aretegraphics.cpp \
    dialogdata.cpp \
    graphescene.cpp \
    main.cpp \
    mainwindow.cpp \
    sommetgraphics.cpp

HEADERS += \
    Arbre.h \
    Graphe.h \
    GrapheNonOriente.h \
    GrapheNonOrienteValue.h \
    GrapheOriente.h \
    GrapheOrienteValue.h \
    aretegraphics.h \
    dialogdata.h \
    graphescene.h \
    mainwindow.h \
    sommetgraphics.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
