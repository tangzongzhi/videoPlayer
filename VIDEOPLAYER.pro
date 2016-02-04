#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T17:00:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VIDEOPLAYER
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

INCLUDEPATH += "C:\opencv\build\include"
INCLUDEPATH += "C:\opencv\build\include\opencv"
INCLUDEPATH += "C:\opencv\build\include\opencv2"




HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): {
LIBS += -LC:/opencv/build/x86/vc12/lib \
-lopencv_core248 \
-lopencv_highgui248 \
-lopencv_imgproc248 \
-lopencv_features2d248 \
-lopencv_calib3d248
} else:win32:CONFIG(debug, debug|release): {
LIBS += -LC:/opencv/build/x86/vc12/lib \
-lopencv_core248d \
-lopencv_highgui248d \
-lopencv_imgproc248d \
-lopencv_features2d248d \
-lopencv_calib3d248d
}
