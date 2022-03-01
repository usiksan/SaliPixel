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
    Mode/SpModeCircle.cpp \
    Mode/SpModeLine.cpp \
    Mode/SpModePoint.cpp \
    Mode/SpModeRect.cpp \
    Win/SpWinEditor.cpp \
    main.cpp \
    Win/SpWinMain.cpp

HEADERS += \
    Mode/SpColor.h \
    Mode/SpImage.h \
    Mode/SpMode.h \
    Mode/SpModeArc.h \
    Mode/SpModeCircle.h \
    Mode/SpModeLine.h \
    Mode/SpModePoint.h \
    Mode/SpModeRect.h \
    SpConfig.h \
    Win/SpWinEditor.h \
    Win/SpWinMain.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
