#include "settingswidgetbase.hpp"
#include "ui_settingswidgetbase.h"

SettingsWidgetBase::SettingsWidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidgetBase)
{
    ui->setupUi(this);
}

SettingsWidgetBase::~SettingsWidgetBase()
{
    delete ui;
}

void SettingsWidgetBase::visible(bool val)
{
    ui->fav_button->setChecked(val);
    setVisible(val);
}

void SettingsWidgetBase::favourite(bool val)
{
    ui->fav_button->setChecked(val);
    emit favourite_changed(val);
}

bool SettingsWidgetBase::favourite()
{
    return ui->fav_button->isChecked();
}

void SettingsWidgetBase::on_fav_button_toggled(bool checked)
{
    favourite(checked);
}
