#include "maillist.hpp"
#include "ui_maillist.h"

MailList::MailList(const QString &text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailList)
{
    ui->setupUi(this);
    ui->text->setText(text);
}

MailList::~MailList()
{
    delete ui;
}
