#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T11:37:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionSystem_ULTIMATE_QT
TEMPLATE = app

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
QMAKE_CXXFLAGS_RELEASE *= -O3

RC_ICONS = gpr.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    Ball.cpp \
    Build_Robot.cpp \
    Configurations.cpp \
    Robot.cpp \
    Segmentation.cpp \
    controlador.cpp \
    Grouping.cpp \
    serialcomm.cpp \
    constantes_robot.cpp \
    strategy.cpp

HEADERS  += mainwindow.h \
    Ball.h \
    Build_Robot.h \
    Configurations.h \
    controlador.h \
    Grouping.h \
    Robot.h \
    Segmentation.h \
    serialcomm.h \
    constantes_robot.h \
    strategy.h

FORMS    += mainwindow.ui \
    constantes_robot.ui

INCLUDEPATH += C:/OpenCV-QT/mybuild/install/include

LIBS += -LC:\\OpenCV-QT\\mybuild\\bin \
    libopencv_core2411 \
    libopencv_calib3d2411 \
    libopencv_contrib2411 \
    libopencv_flann2411 \
    libopencv_gpu2411 \
    libopencv_highgui2411 \
    libopencv_imgproc2411 \
    libopencv_legacy2411 \
    libopencv_ml2411 \
    libopencv_nonfree2411 \
    libopencv_objdetect2411 \
    libopencv_ocl2411 \
    libopencv_photo2411 \
    libopencv_stitching2411 \
    libopencv_superres2411 \
    libopencv_video2411 \
    libopencv_videostab2411 \
    libopencv_features2d2411 \

RESOURCES += \
    recurso.qrc
