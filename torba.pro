#-------------------------------------------------
#
# Torba software project file
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = torba
TEMPLATE = app
CONFIG  += c++14

SOURCES += main.cpp\
    gui/mainwindow.cpp \
    gui/main_widget/mainwidget.cpp \
    gui/main_widget/personwidget.cpp \
    gui/main_widget/eventwidget.cpp \
    gui/main_widget/editorbase.cpp \
    gui/main_widget/mailfilter.cpp \
    gui/settings/settings.cpp \
    gui/settings/settingswidgetbase.cpp \
    gui/settings/savefile.cpp \
    gui/settings/newdatabase.cpp \
    gui/settings/importdatabase.cpp \
    gui/settings/personsettings.cpp \
    gui/settings/eventsettings.cpp \
    gui/settings/searchmailsetting.cpp \
    gui/bottom_bar/bottombar.cpp \
    gui/dialogs/openpersondialog.cpp \
    gui/dialogs/openeventdialog.cpp \
    backend/config.cpp \
    backend/database.cpp \
    backend/entities/personbaseentity.cpp \
    backend/entities/personentity.cpp \
    backend/entities/eventbaseentity.cpp \
    backend/entities/evententity.cpp \
    backend/logger.cpp \
    gui/dialogs/messagedialog.cpp

HEADERS  += \
    gui/mainwindow.hpp \
    gui/main_widget/mainwidget.hpp \
    gui/main_widget/personwidget.hpp \
    gui/main_widget/editorbase.hpp \
    gui/main_widget/eventwidget.hpp \
    gui/main_widget/mailfilter.hpp \
    gui/settings/settings.hpp \
    gui/settings/settingswidgetbase.hpp \
    gui/settings/savefile.hpp \
    gui/settings/newdatabase.hpp \
    gui/settings/importdatabase.hpp \
    gui/settings/personsettings.hpp \
    gui/settings/eventsettings.hpp \
    gui/settings/searchmailsetting.hpp \
    gui/bottom_bar/bottombar.hpp \
    gui/dialogs/openpersondialog.hpp \
    gui/dialogs/openeventdialog.hpp \
    backend/config.hpp \
    backend/database.hpp \
    backend/entities/personbaseentity.hpp \
    backend/entities/evententity.hpp \
    backend/entities/personentity.hpp \
    backend/entities/eventbaseentity.hpp \
    backend/logger.hpp \
    gui/dialogs/messagedialog.hpp

FORMS    += gui/mainwindow.ui \
    gui/main_widget/mainwidget.ui \
    gui/main_widget/personwidget.ui \
    gui/main_widget/eventwidget.ui \
    gui/main_widget/mailfilter.ui \
    gui/settings/settings.ui \
    gui/settings/settingswidgetbase.ui \
    gui/bottom_bar/bottombar.ui \
    gui/dialogs/openpersondialog.ui \
    gui/dialogs/openeventdialog.ui \
    gui/dialogs/messagedialog.ui

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    README.md
