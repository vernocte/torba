#ifndef SEARCHMAILSETTING_HPP
#define SEARCHMAILSETTING_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"

class SearchMailSetting : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit SearchMailSetting(QWidget *parent = 0);
    ~SearchMailSetting();

public slots:

signals:
    void new_mail_filter();

private slots:
    void on_mail_button_clicked();

private:

    QPushButton* mail_button;
};

#endif // SEARCHMAILSETTING_HPP
