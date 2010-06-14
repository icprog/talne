# #####################################################################
# Automatically generated by qmake (2.01a) ?? ????. 21 22:29:12 2010
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    mnemo
INCLUDEPATH += .
QT += sql \
    svg \
    network

# Input
HEADERS += mainform.h \
    mnemo.h \
    sparamdialog.h \
    about.h \
    history.h \
    alertviewdialog.h \
    dlgpumpctrl.h \
    dlgsusctrl.h \
    dlgcessctrl.h
FORMS += mainform.ui \
    mnemo.ui \
    sparamdialog.ui \
    about.ui \
    history.ui \
    alertviewdialog.ui \
    dlgpumpctrl.ui \
    dlgsusctrl.ui \
    dlgcessctrl.ui
SOURCES += main.cpp \
    mainform.cpp \
    mnemo.cpp \
    sparamdialog.cpp \
    history.cpp \
    alertviewdialog.cpp \
    dlgpumpctrl.cpp \
    dlgsusctrl.cpp \
    dlgcessctrl.cpp
RESOURCES += mnemo/mnemo.qrc \
    ../../../lib/picture.qrc \
    ../../../pict/lib/valves.qrc \
    text.qrc
MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build
RCC_DIR = build

# OTHER_FILES += test_map.txt \
# list.txt \
# filters_uk.qm
QMAKE_LIBDIR += ../../../lib
LIBS += -lrcada_client
INCLUDEPATH += ../../../lib/include
OTHER_FILES += text/alert.txt \
    ../var.ods \
    text/reg.txt
win32:QTPLUGIN += qsvg
win32:CONFIG += static
PRE_TARGETDEPS += ../../../lib/librcada_client.a
