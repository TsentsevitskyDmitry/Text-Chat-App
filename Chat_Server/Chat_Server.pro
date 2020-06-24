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
    Services/SocketHelper.cpp \
    Services/ClientSocket.cpp \
    Messages/ErrorMessage.cpp \
    Controllers/StatusController.cpp \
    Models/ServerInfo.cpp \
    Services/StatusPipe.cpp \
    Services/PipeHepler.cpp \
    Models/ServerConfig.cpp


HEADERS += \
    Controllers/ServerController.h \
    Services/ClientProcessor.h \
    Models/ClientInfo.h \
    Services/ChatServer.h \
    Messages/BaseMessage.h \
    Messages/ChatMessage.h \
    Messages/RegisterMessage.h \
    Services/SocketHelper.h \
    Services/ClientSocket.h \
    Messages/MessageTypes.h \
    Messages/ErrorMessage.h \
    Controllers/StatusController.h \
    Models/ServerInfo.h \
    Services/StatusPipe.h \
    Services/PipeHepler.h \
    Models/ServerConfig.h
