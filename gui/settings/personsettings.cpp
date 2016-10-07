#include "personsettings.hpp"

#include "ui_settingswidgetbase.h"

#include<QPainter>

PersonSettings::PersonSettings(QWidget *parent) :
    SettingsWidgetBase(parent)
{
    // add buttons
    new_person_button = new QPushButton();
    open_person_button = new QPushButton();
    remove_person_button = new QPushButton();

    // add icons
    new_person_button->setIcon(QIcon(":/icons/icons/add_person.png"));
    open_person_button->setIcon(QIcon(":/icons/icons/open_person.png"));
    remove_person_button->setIcon(QIcon(":/icons/icons/remove_person.png"));

    new_person_button->setIconSize(QSize(32,32));
    open_person_button->setIconSize(QSize(32,32));
    remove_person_button->setIconSize(QSize(32,32));

    // set size
    new_person_button->setMinimumSize(64,64);
    new_person_button->setMaximumSize(64,64);
    open_person_button->setMinimumSize(64,64);
    open_person_button->setMaximumSize(64,64);
    remove_person_button->setMinimumSize(64,64);
    remove_person_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(new_person_button,0,0);
    ui->main_layout->addWidget(open_person_button,0,1);
    ui->main_layout->addWidget(remove_person_button,0,2);

    connect(new_person_button, SIGNAL(clicked()), this, SLOT(on_new_person_button_clicked()));
    connect(open_person_button, SIGNAL(clicked()), this, SLOT(on_open_person_button_clicked()));
    connect(remove_person_button, SIGNAL(clicked()), this, SLOT(on_remove_person_button_clicked()));
}

PersonSettings::~PersonSettings()
{
    new_person_button->deleteLater();
    open_person_button->deleteLater();
    remove_person_button->deleteLater();
}

void PersonSettings::on_new_person_button_clicked()
{
    emit new_person();
}

void PersonSettings::on_open_person_button_clicked()
{
    emit open_person();
}

void PersonSettings::on_remove_person_button_clicked()
{
    emit delete_person();
}
