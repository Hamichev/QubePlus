QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Periph.cpp \
    builder.cpp \
    json.cpp \
    lib/Periph/ADC/ADC.cpp \
    lib/Periph/DATA/DATA.cpp \
    lib/Periph/EXT/EXT.cpp \
    lib/Periph/I2C/I2C.cpp \
    lib/Periph/TIM/TIM.cpp \
    lib/Periph/UART/UART.cpp \
    main.cpp \
    mcu.cpp \
    pin.cpp \
    qubeplus.cpp

HEADERS += \
    Periph.h \
    builder.h \
    json.h \
    lib/Periph/ADC/ADC.h \
    lib/Periph/DATA/DATA.h \
    lib/Periph/EXT/EXT.h \
    lib/Periph/I2C/I2C.h \
    lib/Periph/TIM/TIM.h \
    lib/Periph/UART/UART.h \
    mcu.h \
    pin.h \
    qubeplus.h

FORMS += \
    qubeplus.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
