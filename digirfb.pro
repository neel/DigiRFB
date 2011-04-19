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
    clientsocket.h

SOURCES += \
    resolution.cpp \
    util.cpp \
    rect.cpp \
    commonsocket.cpp \
    packet.cpp \
    messagepacket.cpp \
    screenpacket.cpp \
    clientsocket.cpp \
    main.cpp

LIBS += -lgdi32
