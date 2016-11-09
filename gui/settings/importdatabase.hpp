#ifndef IMPORTDATABASE_HPP
#define IMPORTDATABASE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"

class ImportDatabase : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit ImportDatabase(QWidget *parent = 0);
    ~ImportDatabase();

public slots:

private slots:
    void on_import_database_button_clicked();
    void on_export_database_button_clicked();

signals:

    void export_database();
    void import_database();

private:

    QPushButton* import_database_button;
    QPushButton* export_database_button;
};

#endif // IMPORTDATABASE_HPP
