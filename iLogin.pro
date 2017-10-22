#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T15:08:06
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iLogin
TEMPLATE = app


SOURCES += main.cpp\
    DesktopUI/mainui.cpp \
    DesktopUI/push_button_p.cpp \
    DesktopUI/system_tray_p.cpp \
    DesktopUI/title_widget_p.cpp \
    DesktopUI/input_widget_p.cpp \
    DesktopUI/contral_widget_p.cpp \
    DesktopUI/show_widget.cpp \
    net_contral.cpp \
    settings.cpp \
    singleapplication.cpp \
    DesktopUI/main_menu.cpp \
    DesktopUI/config_widget.cpp \
    DesktopUI/about_widget.cpp


HEADERS  += \
    DesktopUI/mainui.h \
    MobileUI/mainui.h \
    DesktopUI/push_button_p.h \
    DesktopUI/system_tray_p.h \
    DesktopUI/title_widget_p.h \
    DesktopUI/input_widget_p.h \
    DesktopUI/contral_widget_p.h \
    public_data.h \
    DesktopUI/show_widget.h \
    net_contral.h \
    settings.h \
    singleapplication.h \
    DesktopUI/main_menu.h \
    DesktopUI/config_widget.h \
    DesktopUI/about_widget.h


RESOURCES += \
    img.qrc

win32:
RC_ICONS = ./img/icon.ico
