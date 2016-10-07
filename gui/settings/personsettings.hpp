#ifndef PERSONSETTINGS_HPP
#define PERSONSETTINGS_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"


class PersonSettings : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit PersonSettings(QWidget *parent = 0);
    ~PersonSettings();

signals:
    void new_person();
    void open_person();
    void delete_person();

private slots:
    void on_new_person_button_clicked();
    void on_open_person_button_clicked();
    void on_remove_person_button_clicked();

private:

    QPushButton* new_person_button;
    QPushButton* open_person_button;
    QPushButton* remove_person_button;
};

#endif // PERSONSETTINGS_HPP
