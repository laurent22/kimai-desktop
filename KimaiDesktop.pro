#-------------------------------------------------
#
# Project created by QtCreator 2012-05-21T13:30:43
#
#-------------------------------------------------

QT += core gui webkit

TARGET = Kimai
TEMPLATE = app

win32 {
	DESTDIR = S:/xampp/htdocs/kimai/desktop
	RC_FILE = Kimai.rc
}

SOURCES += main.cpp\
        MainWindow.cpp \
    KimaiPath.cpp \
    Config.cpp \
    ConfigDialog.cpp

HEADERS  += MainWindow.h \
    KimaiPath.h \
    Config.h \
    ConfigDialog.h

FORMS    += MainWindow.ui \
    ConfigDialog.ui







