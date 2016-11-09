#include "settings.hpp"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->event_settings_fav->hide();
    ui->find_mail_fav->hide();
    ui->import_database_fav->hide();
    ui->new_database_fav->hide();
    ui->person_settings_fav->hide();
    ui->save_widget_fav->hide();

    // connect favourite to regular
    connect(ui->event_settings, SIGNAL(favourite_changed(bool)), ui->event_settings_fav, SLOT(visible(bool)));
    connect(ui->event_settings_fav, SIGNAL(favourite_changed(bool)), ui->event_settings_fav, SLOT(visible(bool)));
    connect(ui->event_settings_fav, SIGNAL(favourite_changed(bool)), ui->event_settings, SLOT(favourite(bool)));

    connect(ui->find_mail, SIGNAL(favourite_changed(bool)), ui->find_mail_fav, SLOT(visible(bool)));
    connect(ui->find_mail_fav, SIGNAL(favourite_changed(bool)), ui->find_mail_fav, SLOT(visible(bool)));
    connect(ui->find_mail_fav, SIGNAL(favourite_changed(bool)), ui->find_mail, SLOT(favourite(bool)));

    connect(ui->import_database, SIGNAL(favourite_changed(bool)), ui->import_database_fav, SLOT(visible(bool)));
    connect(ui->import_database_fav, SIGNAL(favourite_changed(bool)), ui->import_database_fav, SLOT(visible(bool)));
    connect(ui->import_database_fav, SIGNAL(favourite_changed(bool)), ui->import_database, SLOT(favourite(bool)));

    connect(ui->new_database, SIGNAL(favourite_changed(bool)), ui->new_database_fav, SLOT(visible(bool)));
    connect(ui->new_database_fav, SIGNAL(favourite_changed(bool)), ui->new_database_fav, SLOT(visible(bool)));
    connect(ui->new_database_fav, SIGNAL(favourite_changed(bool)), ui->new_database, SLOT(favourite(bool)));

    connect(ui->person_settings, SIGNAL(favourite_changed(bool)), ui->person_settings_fav, SLOT(visible(bool)));
    connect(ui->person_settings_fav, SIGNAL(favourite_changed(bool)), ui->person_settings_fav, SLOT(visible(bool)));
    connect(ui->person_settings_fav, SIGNAL(favourite_changed(bool)), ui->person_settings, SLOT(favourite(bool)));

    connect(ui->save_widget_person, SIGNAL(favourite_changed(bool)), ui->save_widget_fav, SLOT(visible(bool)));
    connect(ui->save_widget_event, SIGNAL(favourite_changed(bool)), ui->save_widget_fav, SLOT(visible(bool)));
    connect(ui->save_widget_fav, SIGNAL(favourite_changed(bool)), ui->save_widget_fav, SLOT(visible(bool)));
    connect(ui->save_widget_fav, SIGNAL(favourite_changed(bool)), ui->save_widget_person, SLOT(favourite(bool)));
    connect(ui->save_widget_fav, SIGNAL(favourite_changed(bool)), ui->save_widget_event, SLOT(favourite(bool)));

    // connect functionality
    connect(ui->person_settings, SIGNAL(new_person()), this, SLOT(emit_new_person()));
    connect(ui->person_settings_fav, SIGNAL(new_person()), this, SLOT(emit_new_person()));

    connect(ui->person_settings, SIGNAL(open_person()), this, SLOT(emit_open_person()));
    connect(ui->person_settings_fav, SIGNAL(open_person()), this, SLOT(emit_open_person()));

    connect(ui->person_settings, SIGNAL(delete_person()), this, SLOT(emit_delete_person()));
    connect(ui->person_settings_fav, SIGNAL(delete_person()), this, SLOT(emit_delete_person()));

    connect(ui->event_settings, SIGNAL(new_event()), this, SLOT(emit_new_event()));
    connect(ui->event_settings_fav, SIGNAL(new_event()), this, SLOT(emit_new_event()));

    connect(ui->event_settings, SIGNAL(open_event()), this, SLOT(emit_open_event()));
    connect(ui->event_settings_fav, SIGNAL(open_event()), this, SLOT(emit_open_event()));

    connect(ui->event_settings, SIGNAL(delete_event()), this, SLOT(emit_delete_event()));
    connect(ui->event_settings_fav, SIGNAL(delete_event()), this, SLOT(emit_delete_event()));

    connect(ui->find_mail, SIGNAL(new_mail_filter()), this, SLOT(emit_new_mail_filter()));
    connect(ui->find_mail_fav, SIGNAL(new_mail_filter()), this, SLOT(emit_new_mail_filter()));

    connect(ui->new_database, SIGNAL(new_database()), this, SLOT(emit_new_database()));
    connect(ui->new_database_fav, SIGNAL(new_database()), this, SLOT(emit_new_database()));

    connect(ui->new_database, SIGNAL(open_database()), this, SLOT(emit_open_database()));
    connect(ui->new_database_fav, SIGNAL(open_database()), this, SLOT(emit_open_database()));

    connect(ui->save_widget_person, SIGNAL(save_file()), this, SLOT(emit_save_file()));
    connect(ui->save_widget_event, SIGNAL(save_file()), this, SLOT(emit_save_file()));
    connect(ui->save_widget_fav, SIGNAL(save_file()), this, SLOT(emit_save_file()));

    connect(ui->save_widget_person, SIGNAL(save_file_as()), this, SLOT(emit_save_file_as()));
    connect(ui->save_widget_event, SIGNAL(save_file_as()), this, SLOT(emit_save_file_as()));
    connect(ui->save_widget_fav, SIGNAL(save_file_as()), this, SLOT(emit_save_file_as()));

    connect(ui->save_widget_person, SIGNAL(save_all()), this, SLOT(emit_save_all()));
    connect(ui->save_widget_event, SIGNAL(save_all()), this, SLOT(emit_save_all()));
    connect(ui->save_widget_fav, SIGNAL(save_all()), this, SLOT(emit_save_all()));

    connect(ui->import_database, SIGNAL(import_database()), this, SLOT(emit_import_database()));
    connect(ui->import_database_fav, SIGNAL(import_database()), this, SLOT(emit_import_database()));

    connect(ui->import_database, SIGNAL(export_database()), this, SLOT(emit_export_database()));
    connect(ui->import_database_fav, SIGNAL(export_database()), this, SLOT(emit_export_database()));

    ui->settings_stack->setCurrentIndex(0);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::set_favourites(Config& c)
{
    ui->event_settings_fav->favourite(c.event_setting());
    ui->find_mail_fav->favourite(c.find_mail());
    ui->import_database_fav->favourite(c.import_database());
    ui->new_database_fav->favourite(c.new_database());
    ui->person_settings_fav->favourite(c.person_settings());
    ui->save_widget_fav->favourite(c.save_widget());

    ui->settings_stack->setVisible(c.settings_visible());
    ui->hide_button->setChecked(c.settings_visible());
}

void Settings::save_favourites(Config& c)
{
    c.event_setting(ui->event_settings_fav->favourite());
    c.find_mail(ui->find_mail_fav->favourite());
    c.import_database(ui->import_database_fav->favourite());
    c.new_database(ui->new_database_fav->favourite());
    c.person_settings(ui->person_settings_fav->favourite());
    c.save_widget(ui->save_widget_fav->favourite());

    c.settings_visible(ui->hide_button->isChecked());
}

void Settings::emit_new_person()
{
    emit new_person();
}

void Settings::emit_new_event()
{
    emit new_event();
}

void Settings::emit_new_mail_filter()
{
    emit new_mail_filter();
}

void Settings::emit_new_database()
{
    emit new_database();
}

void Settings::emit_open_database()
{
    emit open_database();
}

void Settings::emit_open_person()
{
    emit open_person();
}

void Settings::emit_delete_person()
{
    emit delete_person();
}

void Settings::emit_open_event()
{
    emit open_event();
}

void Settings::emit_delete_event()
{
    emit delete_event();
}

void Settings::emit_save_file()
{
    emit save_file();
}

void Settings::emit_save_file_as()
{
    emit save_file_as();
}

void Settings::emit_save_all()
{
    emit save_all();
}

void Settings::on_favourites_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 0 && ui->settings_stack->isVisible())
    {
        ui->settings_stack->hide();
        ui->hide_button->setChecked(false);
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(0);
    }
}

void Settings::on_database_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 1 && ui->settings_stack->isVisible())
    {
        ui->hide_button->setChecked(false);
        ui->settings_stack->hide();
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(1);
    }
}

void Settings::on_person_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 2 && ui->settings_stack->isVisible())
    {
        ui->hide_button->setChecked(false);
        ui->settings_stack->hide();
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(2);
    }
}

void Settings::on_event_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 3 && ui->settings_stack->isVisible())
    {
        ui->hide_button->setChecked(false);
        ui->settings_stack->hide();
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(3);
    }
}

void Settings::on_about_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 5 && ui->settings_stack->isVisible())
    {
        ui->hide_button->setChecked(false);
        ui->settings_stack->hide();
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(5);
    }
}

void Settings::on_hide_button_clicked()
{
    ui->settings_stack->setVisible(ui->hide_button->isChecked());
}

void Settings::on_find_button_clicked()
{
    if(ui->settings_stack->currentIndex() == 4 && ui->settings_stack->isVisible())
    {
        ui->hide_button->setChecked(false);
        ui->settings_stack->hide();
    }
    else
    {
        ui->hide_button->setChecked(true);
        ui->settings_stack->show();
        ui->settings_stack->setCurrentIndex(4);
    }
}


void Settings::emit_import_database()
{
    emit import_database();
}

void Settings::emit_export_database()
{
    emit export_database();
}
