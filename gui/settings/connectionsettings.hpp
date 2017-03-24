#ifndef CONNECTIONSETTINGS_HPP
#define CONNECTIONSETTINGS_HPP

#include <QCheckBox>

#include "settingswidgetbase.hpp"

class ConnectionSettings : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit ConnectionSettings(QWidget *parent = 0);
    ~ConnectionSettings();

    bool autoconnect();

public slots:

    void autoconnect(bool val);

signals:

    void autoconnect_changed(bool);

private:

    QCheckBox *_autoconnect;

private slots:

    void emit_autoconnect_changed(bool val);
};

#endif // CONNECTIONSETTINGS_HPP
