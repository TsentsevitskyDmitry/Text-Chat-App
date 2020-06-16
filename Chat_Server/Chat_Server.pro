TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32

SOURCES += \
    Controllers/ServerController.cpp \
    Services/ClientProcessor.cpp \
    main.cpp \
    Models/ClientInfo.cpp \
    Services/ChatServer.cpp \
    Messages/BaseMessage.cpp \
    Messages/ChatMessage.cpp \
    Messages/RegisterMessage.cpp \
    Services/ServerSocket.cpp \
    Messages/DataTypeMessage.cpp \
    Services/SocketHelper.cpp


HEADERS += \
    Controllers/ServerController.h \
    Services/ClientProcessor.h \
    Models/ClientInfo.h \
    Services/ChatServer.h \
    Messages/BaseMessage.h \
    Messages/ChatMessage.h \
    Messages/RegisterMessage.h \
    Services/ServerSocket.h \
    Messages/DataTypeMessage.h \
    Messages/MessageType.h \
    Services/SocketHelper.h
