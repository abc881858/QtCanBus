QT -= gui

QT += serialbus

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        frame.cpp \
        main.cpp \
        subscriber.cpp \
        worker.cpp

HEADERS += \
    autonomymode.h \
    frame.h \
    gear.h \
    subscriber.h \
    vehiclecommand.h \
    vehiclereport.h \
    wheelspeedreport.h \
    worker.h

LIBS += /opt/ros/kinetic/lib/librosconsole.so
LIBS += /opt/ros/kinetic/lib/libroscpp_serialization.so
LIBS += /opt/ros/kinetic/lib/librosconsole_log4cxx.so
LIBS += /opt/ros/kinetic/lib/librosconsole_backend_interface.so
LIBS += /opt/ros/kinetic/lib/librostime.so
LIBS += /opt/ros/kinetic/lib/libroscpp.so
LIBS += /opt/ros/kinetic/lib/libcpp_common.so
LIBS += /opt/ros/kinetic/lib/libxmlrpcpp.so

#LIBS += /opt/ros/kinetic/lib/librosbag_storage.so
#LIBS += /opt/ros/kinetic/lib/libroslib.so
#LIBS += /opt/ros/kinetic/lib/librostime.so
#LIBS += /opt/ros/kinetic/lib/libroslz4.so
#LIBS += /opt/ros/kinetic/lib/libroscpp_serialization.so
#LIBS += /opt/ros/kinetic/lib/librospack.so
#LIBS += /opt/ros/kinetic/lib/libcpp_common.so

INCLUDEPATH += /opt/ros/kinetic/include
