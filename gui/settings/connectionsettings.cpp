#include "connectionsettings.hpp"

#include "ui_settingswidgetbase.h"

ConnectionSettings::ConnectionSettings(QWidget *parent) :
    SettingsWidgetBase(parent)
{
       _autoconnect = new QCheckBox();
       _autoconnect->setText("Samodejno poveži");

       connect(_autoconnect, SIGNAL(toggled(bool)), this, SLOT(emit_autoconnect_changed(bool)));

       // add to layout
       ui->main_layout->addWidget(_autoconnect,0,0);
       ui->main_layout->setMargin(12);
}

ConnectionSettings::~ConnectionSettings()
{
       _autoconnect->deleteLater();
}

bool ConnectionSettings::autoconnect()
{
    return _autoconnect->isChecked();
}

void ConnectionSettings::autoconnect(bool val)
{
    return _autoconnect->setChecked(val);
}

void ConnectionSettings::emit_autoconnect_changed(bool val)
{
    emit autoconnect_changed(val);
}
