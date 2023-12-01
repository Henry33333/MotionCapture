#-------------------------------------------------
#
# Project created by QtCreator 2023-11-12T10:45:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotionCapture_Interface
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
        main.cpp \
        mainwindow.cpp

HEADERS += \
        QXlsx/include/xlsxabstractooxmlfile.h \
        QXlsx/include/xlsxabstractooxmlfile_p.h \
        QXlsx/include/xlsxabstractsheet.h \
        QXlsx/include/xlsxabstractsheet_p.h \
        QXlsx/include/xlsxcell.h \
        QXlsx/include/xlsxcell_p.h \
        QXlsx/include/xlsxcellformula.h \
        QXlsx/include/xlsxcellformula_p.h \
        QXlsx/include/xlsxcelllocation.h \
        QXlsx/include/xlsxcellrange.h \
        QXlsx/include/xlsxcellreference.h \
        QXlsx/include/xlsxchart.h \
        QXlsx/include/xlsxchart_p.h \
        QXlsx/include/xlsxchartsheet.h \
        QXlsx/include/xlsxchartsheet_p.h \
        QXlsx/include/xlsxcolor_p.h \
        QXlsx/include/xlsxconditionalformatting.h \
        QXlsx/include/xlsxconditionalformatting_p.h \
        QXlsx/include/xlsxcontenttypes_p.h \
        QXlsx/include/xlsxdatavalidation.h \
        QXlsx/include/xlsxdatavalidation_p.h \
        QXlsx/include/xlsxdatetype.h \
        QXlsx/include/xlsxdocpropsapp_p.h \
        QXlsx/include/xlsxdocpropscore_p.h \
        QXlsx/include/xlsxdocument.h \
        QXlsx/include/xlsxdocument_p.h \
        QXlsx/include/xlsxdrawing_p.h \
        QXlsx/include/xlsxdrawinganchor_p.h \
        QXlsx/include/xlsxformat.h \
        QXlsx/include/xlsxformat_p.h \
        QXlsx/include/xlsxglobal.h \
        QXlsx/include/xlsxmediafile_p.h \
        QXlsx/include/xlsxnumformatparser_p.h \
        QXlsx/include/xlsxrelationships_p.h \
        QXlsx/include/xlsxrichstring.h \
        QXlsx/include/xlsxrichstring_p.h \
        QXlsx/include/xlsxsharedstrings_p.h \
        QXlsx/include/xlsxsimpleooxmlfile_p.h \
        QXlsx/include/xlsxstyles_p.h \
        QXlsx/include/xlsxtheme_p.h \
        QXlsx/include/xlsxutility_p.h \
        QXlsx/include/xlsxworkbook.h \
        QXlsx/include/xlsxworkbook_p.h \
        QXlsx/include/xlsxworksheet.h \
        QXlsx/include/xlsxworksheet_p.h \
        QXlsx/include/xlsxzipreader_p.h \
        QXlsx/include/xlsxzipwriter_p.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QXlsx/bin64/ -lQXlsx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QXlsx/bin64/ -lQXlsxd

INCLUDEPATH += $$PWD/QXlsx/include
DEPENDPATH += $$PWD/QXlsx/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/QXlsx/bin64/libQXlsx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/QXlsx/bin64/libQXlsxd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/QXlsx/bin64/QXlsx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/QXlsx/bin64/QXlsxd.lib
