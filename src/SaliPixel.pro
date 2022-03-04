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
    Mode/SpModeArea.cpp \
    Mode/SpModeAreaMirror.cpp \
    Mode/SpModeAreaMove.cpp \
    Mode/SpModeAreaRectArray.cpp \
    Mode/SpModeAreaRotate.cpp \
    Mode/SpModeAreaRoundArray.cpp \
    Mode/SpModeAreaScale.cpp \
    Mode/SpModeCircle.cpp \
    Mode/SpModeCircle2.cpp \
    Mode/SpModeClearCircle.cpp \
    Mode/SpModeClearPoint.cpp \
    Mode/SpModeClearRect.cpp \
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
    Object/SpCmdArea.cpp \
    Object/SpCmdAreaMirror.cpp \
    Object/SpCmdAreaMove.cpp \
    Object/SpCmdAreaRectArray.cpp \
    Object/SpCmdAreaRotate.cpp \
    Object/SpCmdAreaRoundArray.cpp \
    Object/SpCmdAreaScale.cpp \
    Object/SpCmdCircle.cpp \
    Object/SpCmdClearCircle.cpp \
    Object/SpCmdClearPoint.cpp \
    Object/SpCmdClearRect.cpp \
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
    Mode/SpModeArea.h \
    Mode/SpModeAreaMirror.h \
    Mode/SpModeAreaMove.h \
    Mode/SpModeAreaRectArray.h \
    Mode/SpModeAreaRotate.h \
    Mode/SpModeAreaRoundArray.h \
    Mode/SpModeAreaScale.h \
    Mode/SpModeCircle.h \
    Mode/SpModeCircle2.h \
    Mode/SpModeClearCircle.h \
    Mode/SpModeClearPoint.h \
    Mode/SpModeClearRect.h \
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
    Object/SpCmdArea.h \
    Object/SpCmdAreaMirror.h \
    Object/SpCmdAreaMove.h \
    Object/SpCmdAreaRectArray.h \
    Object/SpCmdAreaRotate.h \
    Object/SpCmdAreaRoundArray.h \
    Object/SpCmdAreaScale.h \
    Object/SpCmdCircle.h \
    Object/SpCmdClearCircle.h \
    Object/SpCmdClearPoint.h \
    Object/SpCmdClearRect.h \
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
