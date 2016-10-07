#include "searchmailsetting.hpp"
#include "ui_settingswidgetbase.h"

SearchMailSetting::SearchMailSetting(QWidget *parent) : SettingsWidgetBase(parent)
{
    // add buttons
    mail_button = new QPushButton();

    // add icons
    mail_button->setIcon(QIcon(":/icons/icons/mail.png"));

    mail_button->setIconSize(QSize(32,32));

    // set size
    mail_button->setMinimumSize(64,64);
    mail_button->setMaximumSize(64,64);

    // add to layout
    ui->main_layout->addWidget(mail_button,0,0);

    // pushing to the left
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->main_layout->addWidget(empty,0,1);

    connect(mail_button, SIGNAL(clicked()), this, SLOT(on_mail_button_clicked()));
}

SearchMailSetting::~SearchMailSetting()
{
    mail_button->deleteLater();
}

void SearchMailSetting::on_mail_button_clicked()
{
    emit new_mail_filter();
}
