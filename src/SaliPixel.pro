QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Mode/SpColor.cpp \
    Mode/SpImage.cpp \
    Mode/SpMode.cpp \
    Mode/SpModeArc.cpp \
    Mode/SpModeArc2.cpp \
    Mode/SpModeCircle.cpp \
    Mode/SpModeCircle2.cpp \
    Mode/SpModeFill.cpp \
    Mode/SpModeFillCircle.cpp \
    Mode/SpModeFillRect.cpp \
    Mode/SpModeIdle.cpp \
    Mode/SpModeLine.cpp \
    Mode/SpModePoint.cpp \
    Mode/SpModeRect.cpp \
    Mode/SpModeTriangle.cpp \
    Object/SpCmd.cpp \
    Object/SpCmdArc.cpp \
    Object/SpCmdCircle.cpp \
    Object/SpCmdFill.cpp \
    Object/SpCmdFillCircle.cpp \
    Object/SpCmdFillRect.cpp \
    Object/SpCmdLine.cpp \
    Object/SpCmdPoint.cpp \
    Object/SpCmdRect.cpp \
    Object/SpCmdTriangle.cpp \
    Win/SpDlgNew.cpp \
    Win/SpWinEditor.cpp \
    main.cpp \
    Win/SpWinMain.cpp


HEADERS += \
    Mode/SpColor.h \
    Mode/SpImage.h \
    Mode/SpMode.h \
    Mode/SpModeArc.h \
    Mode/SpModeArc2.h \
    Mode/SpModeCircle.h \
    Mode/SpModeCircle2.h \
    Mode/SpModeFill.h \
    Mode/SpModeFillCircle.h \
    Mode/SpModeFillRect.h \
    Mode/SpModeIdle.h \
    Mode/SpModeLine.h \
    Mode/SpModePoint.h \
    Mode/SpModeRect.h \
    Mode/SpModeTriangle.h \
    Object/SpCmd.h \
    Object/SpCmdArc.h \
    Object/SpCmdCircle.h \
    Object/SpCmdFill.h \
    Object/SpCmdFillCircle.h \
    Object/SpCmdFillRect.h \
    Object/SpCmdLine.h \
    Object/SpCmdPoint.h \
    Object/SpCmdRect.h \
    Object/SpCmdTriangle.h \
    SpConfig.h \
    Win/SpDlgNew.h \
    Win/SpWinEditor.h \
    Win/SpWinMain.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
  Win/SpDlgNew.ui
