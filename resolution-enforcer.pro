qmake
QT += core gui widgets
TARGET = ResolutionEnforcer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    resolutionmanager.cpp \
    config.cpp

HEADERS += \
    mainwindow.h \
    resolutionmanager.h \
    config.h

LIBS += -luser32 -lgdi32
