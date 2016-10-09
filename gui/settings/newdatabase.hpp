#ifndef NEWDATABASE_HPP
#define NEWDATABASE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"

class NewDatabase : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit NewDatabase(QWidget *parent = 0);
    ~NewDatabase();

signals:
    void new_database();
    void open_database();

private slots:
    void on_new_database_button_clicked();
    void on_open_database_button_clicked();

private:

    QPushButton* new_database_button;
    QPushButton* open_database_button;
};

#endif // NEWDATABASE_HPP
