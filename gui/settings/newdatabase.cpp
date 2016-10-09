#include "newdatabase.hpp"
#include "ui_settingswidgetbase.h"
#include <QFileDialog>

NewDatabase::NewDatabase(QWidget *parent) :
    SettingsWidgetBase(parent)
{
    // add buttons
    new_database_button = new QPushButton();
    open_database_button = new QPushButton();

    // add icons
    new_database_button->setIcon(QIcon(":/icons/icons/new_database.png"));
    open_database_button->setIcon(QIcon(":/icons/icons/open_database.png"));

    new_database_button->setIconSize(QSize(32,32));
    open_database_button->setIconSize(QSize(32,32));

    // set size
    new_database_button->setMinimumSize(64,64);
    new_database_button->setMaximumSize(64,64);
    open_database_button->setMinimumSize(64,64);
    open_database_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(new_database_button,0,0);
    ui->main_layout->addWidget(open_database_button,0,1);

    // pushing to the left
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->main_layout->addWidget(empty,0,2);

    connect(new_database_button, SIGNAL(clicked()), this, SLOT(on_new_database_button_clicked()));
    connect(open_database_button, SIGNAL(clicked()), this, SLOT(on_open_database_button_clicked()));
}

NewDatabase::~NewDatabase()
{
    new_database_button->deleteLater();
    open_database_button->deleteLater();
}

void NewDatabase::on_new_database_button_clicked()
{
    emit new_database();
}

void NewDatabase::on_open_database_button_clicked()
{
    emit open_database();
}
