QT       += core gui network datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Worker.cpp \
    cali.cpp \
    dif.cpp \
    hybrid/hybrid.cpp \
    hybrid/hybrid_data.cpp \
    hybrid/hybrid_initialize.cpp \
    hybrid/hybrid_rtwutil.cpp \
    hybrid/hybrid_terminate.cpp \
    hybrid/mldivide.cpp \
    hybrid/rtGetInf.cpp \
    hybrid/rtGetNaN.cpp \
    hybrid/rt_nonfinite.cpp \
    hybrid/schur.cpp \
    hybrid/sqrt.cpp \
    hybrid/svd.cpp \
    hybrid/vlogR.cpp \
    hybrid/xaxpy.cpp \
    hybrid/xdlanv2.cpp \
    hybrid/xdotc.cpp \
    hybrid/xgerc.cpp \
    hybrid/xhseqr.cpp \
    hybrid/xnrm2.cpp \
    hybrid/xrot.cpp \
    hybrid/xrotg.cpp \
    hybrid/xswap.cpp \
    hybrid/xzggev.cpp \
    hybrid/xzhgeqz.cpp \
    hybrid/xzlartg.cpp \
    hybrid/xztgevc.cpp \
    main.cpp \
    mainwindow.cpp \
    scatterdatamodifier.cpp

HEADERS += \
    EstunRemoteApiLib/AddDoTypeConvert.h \
    EstunRemoteApiLib/EstunFtpLib.h \
    EstunRemoteApiLib/EstunRemoteApiLib.h \
    EstunRemoteApiLib/EstunRemoteApiLib_define.h \
    EstunRemoteApiLib/EstunRemoteApiLib_global.h \
    EstunRemoteApiLib/EstunRemoteApiLib_struct.h \
    SeekerSDKCAPI.h \
    SeekerSDKClient.h \
    SeekerSDKTypes.h \
    StructDef.h \
    Utility.h \
    Worker.h \
    cali.h \
    dif.h \
    hybrid/hybrid.h \
    hybrid/hybrid_data.h \
    hybrid/hybrid_initialize.h \
    hybrid/hybrid_rtwutil.h \
    hybrid/hybrid_terminate.h \
    hybrid/hybrid_types.h \
    hybrid/mldivide.h \
    hybrid/rtGetInf.h \
    hybrid/rtGetNaN.h \
    hybrid/rt_nonfinite.h \
    hybrid/rtwtypes.h \
    hybrid/schur.h \
    hybrid/sqrt.h \
    hybrid/svd.h \
    hybrid/tmwtypes.h \
    hybrid/vlogR.h \
    hybrid/xaxpy.h \
    hybrid/xdlanv2.h \
    hybrid/xdotc.h \
    hybrid/xgerc.h \
    hybrid/xhseqr.h \
    hybrid/xnrm2.h \
    hybrid/xrot.h \
    hybrid/xrotg.h \
    hybrid/xswap.h \
    hybrid/xzggev.h \
    hybrid/xzhgeqz.h \
    hybrid/xzlartg.h \
    hybrid/xztgevc.h \
    mainwindow.h \
    scatterdatamodifier.h \
    x1motlibface.h

FORMS += \
    dif.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



LIBS += -L$$PWD/lib/ -lnokov_sdk
LIBS += -L$$PWD/lib/ -lX1RobHalLib
LIBS += -L$$PWD/lib/ -lEstunRemoteApiLib-vc140-x64
LIBS += -lwsock32


QXLSX_PARENTPATH=$$PWD/
QXLSX_HEADERPATH=$$PWD/QXlsx/header/
QXLSX_SOURCEPATH=$$PWD/QXlsx/source/
include($$PWD/QXlsx.pri)
