#ifndef EVENTSETTINGS_HPP
#define EVENTSETTINGS_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"


class EventSettings : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit EventSettings(QWidget *parent = 0);
    ~EventSettings();

signals:
    void new_event();
    void open_event();
    void delete_event();

private slots:
    void on_new_event_button_clicked();
    void on_open_event_button_clicked();
    void on_remove_event_button_clicked();

private:

    QPushButton* new_event_button;
    QPushButton* open_event_button;
    QPushButton* remove_event_button;
};

#endif // EVENTSETTINGS_HPP
