#include "savefile.hpp"
#include "ui_settingswidgetbase.h"

#include<QPainter>

SaveFile::SaveFile(QWidget *parent) :
    SettingsWidgetBase(parent)
{

    // add buttons
    save_button = new QPushButton();
    save_as_button = new QPushButton();
    save_all_button = new QPushButton();

    // add icons
    save_button->setIcon(QIcon(":/icons/icons/save.png"));
    save_as_button->setIcon(QIcon(":/icons/icons/save_as.png"));
    save_all_button->setIcon(QIcon(":/icons/icons/save_all.png"));

    save_button->setIconSize(QSize(32,32));
    save_as_button->setIconSize(QSize(32,32));
    save_all_button->setIconSize(QSize(32,32));

    // set size
    save_button->setMinimumSize(64,64);
    save_button->setMaximumSize(64,64);
    save_as_button->setMinimumSize(64,64);
    save_as_button->setMaximumSize(64,64);
    save_all_button->setMinimumSize(64,64);
    save_all_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(save_button,0,0);
    ui->main_layout->addWidget(save_as_button,0,1);
    ui->main_layout->addWidget(save_all_button,0,2);

    connect(save_button, SIGNAL(clicked()), this, SLOT(on_save_button_clicked()));
    connect(save_as_button, SIGNAL(clicked()), this, SLOT(on_save_as_button_clicked()));
}

SaveFile::~SaveFile()
{
    save_button->deleteLater();
    save_as_button->deleteLater();
    save_all_button->deleteLater();
}

void SaveFile::on_save_button_clicked()
{
    emit save_file();
}

void SaveFile::on_save_as_button_clicked()
{
    emit save_file_as();
}

void SaveFile::on_save_all_button_clicked()
{
    emit save_all();
}
