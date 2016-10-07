#include "importdatabase.hpp"
#include "ui_settingswidgetbase.h"

ImportDatabase::ImportDatabase(QWidget *parent) :
    SettingsWidgetBase(parent)
{
    // add buttons
    import_database_button = new QPushButton();
    export_database_button = new QPushButton();

    // add icons
    import_database_button->setIcon(QIcon(":/icons/icons/import_database.png"));
    export_database_button->setIcon(QIcon(":/icons/icons/export_database.png"));

    import_database_button->setIconSize(QSize(32,32));
    export_database_button->setIconSize(QSize(32,32));

    // set size
    import_database_button->setMinimumSize(64,64);
    import_database_button->setMaximumSize(64,64);
    export_database_button->setMinimumSize(64,64);
    export_database_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(import_database_button,0,0);
    ui->main_layout->addWidget(export_database_button,0,1);

    // pushing to the left
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->main_layout->addWidget(empty,0,2);

    connect(import_database_button, SIGNAL(clicked()), this, SLOT(on_import_database_button_clicked()));
    connect(export_database_button, SIGNAL(clicked()), this, SLOT(on_export_database_button_clicked()));
}

ImportDatabase::~ImportDatabase()
{
    import_database_button->deleteLater();
    export_database_button->deleteLater();
}

void ImportDatabase::on_import_database_button_clicked()
{

}

void ImportDatabase::on_export_database_button_clicked()
{

}
