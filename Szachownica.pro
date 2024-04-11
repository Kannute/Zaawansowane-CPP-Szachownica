#-------------------------------------------------
#
# Project created by QtCreator 2024-03-18T19:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Szachownica
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        basepawn.cpp \
        bishopmodel.cpp \
        boardborderfield.cpp \
        boardfield.cpp \
        boardinterface.cpp \
        boardmodel.cpp \
        button.cpp \
        constants.cpp \
        gameinterface.cpp \
        kingmodel.cpp \
        knightmodel.cpp \
        main.cpp \
        pawnfield.cpp \
        pawninterface.cpp \
        pawnmodel.cpp \
        playerinterface.cpp \
        queenmodel.cpp \
        rookmodel.cpp \
        utils.cpp \
        winnerinterface.cpp

HEADERS += \
        basepawn.h \
        bishopmodel.h \
        boardborderfield.h \
        boardfield.h \
        boardinterface.h \
        boardmodel.h \
        boardposition.h \
        button.h \
        constants.h \
        gameinterface.h \
        helpers.h \
        kingmodel.h \
        knightmodel.h \
        pawnfield.h \
        pawninterface.h \
        pawnmodel.h \
        playerinterface.h \
        queenmodel.h \
        rookmodel.h \
        utils.h \
        winnerinterface.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
