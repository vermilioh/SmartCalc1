QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_smart_calc.c \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    x_window.cpp

HEADERS += \
    ../s21_smart_calc.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h \
    x_window.h

FORMS += \
    graph.ui \
    mainwindow.ui \
    x_window.ui

ICON = grave.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
