#include "eventsettings.hpp"

#include "ui_settingswidgetbase.h"

#include<QPainter>

EventSettings::EventSettings(QWidget *parent) :
    SettingsWidgetBase(parent)
{
    // add buttons
    new_event_button = new QPushButton();
    open_event_button = new QPushButton();
    remove_event_button = new QPushButton();

    // add icons
    new_event_button->setIcon(QIcon(":/icons/icons/add_event.png"));
    open_event_button->setIcon(QIcon(":/icons/icons/open_event.png"));
    remove_event_button->setIcon(QIcon(":/icons/icons/remove_event.png"));

    new_event_button->setIconSize(QSize(32,32));
    open_event_button->setIconSize(QSize(32,32));
    remove_event_button->setIconSize(QSize(32,32));

    // set size
    new_event_button->setMinimumSize(64,64);
    new_event_button->setMaximumSize(64,64);
    open_event_button->setMinimumSize(64,64);
    open_event_button->setMaximumSize(64,64);
    remove_event_button->setMinimumSize(64,64);
    remove_event_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(new_event_button,0,0);
    ui->main_layout->addWidget(open_event_button,0,1);
    ui->main_layout->addWidget(remove_event_button,0,2);

    connect(new_event_button, SIGNAL(clicked()), this, SLOT(on_new_event_button_clicked()));
    connect(open_event_button, SIGNAL(clicked()), this, SLOT(on_open_event_button_clicked()));
    connect(remove_event_button, SIGNAL(clicked()), this, SLOT(on_remove_event_button_clicked()));
}

EventSettings::~EventSettings()
{
    new_event_button->deleteLater();
    open_event_button->deleteLater();
    remove_event_button->deleteLater();
}

void EventSettings::on_new_event_button_clicked()
{
    emit new_event();
}

void EventSettings::on_open_event_button_clicked()
{
    emit open_event();
}

void EventSettings::on_remove_event_button_clicked()
{
    emit delete_event();
}
