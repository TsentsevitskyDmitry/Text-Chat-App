#-------------------------------------------------
#
# Project created by QtCreator 2020-06-09T23:11:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat_Client
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

CONFIG += c++17
LIBS += -lws2_32

SOURCES += \
        main.cpp \
    Messages/ChatMessage.cpp \
    Service/ChatClient.cpp \
    Controllers/ChatViewController.cpp \
    Messages/RegisterMessage.cpp \
    Messages/BaseMessage.cpp \
    Service/SocketHelper.cpp \
    Service/ServerSocket.cpp \
    Messages/ErrorMessage.cpp \
    Service/ErrorHelper.cpp \
    Views/MainWindow.cpp \
    Views/ConnectDialog.cpp \
    Models/ConnectionSettings.cpp \
    Controllers/ConnectDialogController.cpp

HEADERS += \
    Messages/ChatMessage.h \
    Service/ChatClient.h \
    Controllers/ChatViewController.h \
    Messages/RegisterMessage.h \
    Messages/BaseMessage.h \
    Service/SocketHelper.h \
    Service/ServerSocket.h \
    Messages/MessageTypes.h \
    Messages/ErrorMessage.h \
    Service/ErrorHelper.h \
    Views/MainWindow.h \
    Views/ConnectDialog.h \
    Models/ConnectionSettings.h \
    Controllers/ConnectDialogController.h

FORMS += \
    Views/mainwindow.ui \
    Views/connectdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
