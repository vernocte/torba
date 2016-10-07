#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QWidget>
#include "../../backend/config.hpp"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

public slots:
    void set_favourites(Config &c);
    void save_favourites(Config& c);

signals:
    void new_person();
    void new_event();
    void new_mail_filter();
    void new_database(QString);
    void open_database(QString);
    void open_person();
    void delete_person();
    void open_event();
    void delete_event();
    void save_file();
    void save_file_as();
    void save_all();

private slots:
    void on_favourites_button_clicked();
    void on_database_button_clicked();
    void on_person_button_clicked();
    void on_event_button_clicked();
    void on_about_button_clicked();
    void on_hide_button_clicked();
    void on_find_button_clicked();

    void emit_new_person();
    void emit_open_person();
    void emit_delete_person();
    void emit_new_event();
    void emit_open_event();
    void emit_delete_event();
    void emit_new_mail_filter();
    void emit_new_database(QString);
    void emit_open_database(QString);
    void emit_save_file();
    void emit_save_file_as();
    void emit_save_all();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_HPP
