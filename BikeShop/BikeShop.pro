TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bike.cpp \
        boss.cpp \
        main.cpp \
        profile.cpp \
        rent.cpp \
        renter.cpp \
        worker.cpp

HEADERS += \
    bike.h \
    boss.h \
    profile.h \
    rent.h \
    renter.h \
    worker.h
