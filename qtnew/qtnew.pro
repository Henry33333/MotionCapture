QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    track.cpp

HEADERS += \
    mainwindow.h \
    track.h

FORMS += \
    mainwindow.ui \
    track.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/thirdParty/cxxopts

#

win32: LIBS += -L$$PWD/lib/release/ -lKortexApiCpp

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/messages
INCLUDEPATH += $$PWD/include/client
INCLUDEPATH += $$PWD/include/client_stubs
INCLUDEPATH += $$PWD/include/google
INCLUDEPATH += $$PWD/include/common
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/release/KortexApiCpp.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/release/libKortexApiCpp.a
