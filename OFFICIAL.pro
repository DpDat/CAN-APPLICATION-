QT += core gui serialport serialbus charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphwindow.cpp \
    honda1.cpp \
    honda_decode.cpp \
    honda_monitor.cpp \
    honda_rtr.cpp \
    hynndai.cpp \
    hyundai_decode.cpp \
    hyundai_monitor.cpp \
    hyundai_rtr.cpp \
    main.cpp \
    mainwindow.cpp \
    mazda.cpp \
    mazda_decode.cpp \
    mazda_monitor.cpp \
    mazda_rtr.cpp \
    mazda_signal.cpp \
    tesla.cpp \
    tesla_decode.cpp \
    tesla_monitor.cpp \
    tesla_rtr.cpp

HEADERS += \
    graphwindow.h \
    honda1.h \
    honda_decode.h \
    honda_monitor.h \
    honda_rtr.h \
    hynndai.h \
    hyundai_decode.h \
    hyundai_monitor.h \
    hyundai_rtr.h \
    mainwindow.h \
    mazda.h \
    mazda_decode.h \
    mazda_monitor.h \
    mazda_rtr.h \
    mazda_signal.h \
    tesla.h \
    tesla_decode.h \
    tesla_monitor.h \
    tesla_rtr.h

FORMS += \
    honda1.ui \
    honda_decode.ui \
    honda_monitor.ui \
    honda_rtr.ui \
    hynndai.ui \
    hyundai_decode.ui \
    hyundai_monitor.ui \
    hyundai_rtr.ui \
    mainwindow.ui \
    mazda.ui \
    mazda_decode.ui \
    mazda_monitor.ui \
    mazda_rtr.ui \
    mazda_signal.ui \
    tesla.ui \
    tesla_decode.ui \
    tesla_monitor.ui \
    tesla_rtr.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ResourcesFile.qrc
