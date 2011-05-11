QT += core gui network

TARGET = DGRFB
TEMPLATE = app

HEADERS += \
    resolution.h \
    util.h \
    rect.h \
    commonsocket.h \
    packet.h \
    messagepacket.h \
    screenpacket.h \
    clientsocket.h \
    serversocket.h \
    matrixstorage.h \
    matrixstorageitem.h \
    rectarea.h \
    updatethread.h \
    server.h \
    requestcontroller.h \
    screenviewerwidget.h \
    scenematrix.h

SOURCES += \
    resolution.cpp \
    util.cpp \
    rect.cpp \
    commonsocket.cpp \
    packet.cpp \
    messagepacket.cpp \
    screenpacket.cpp \
    clientsocket.cpp \
    main.cpp \
    serversocket.cpp \
    matrixstorage.cpp \
    matrixstorageitem.cpp \
    rectarea.cpp \
    updatethread.cpp \
    server.cpp \
    requestcontroller.cpp \
    screenviewerwidget.cpp \
    scenematrix.cpp

LIBS += -lgdi32
