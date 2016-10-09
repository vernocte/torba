#include "mailfilter.hpp"
#include "ui_mailfilter.h"


MailFilter::MailFilter(QWidget *parent)  :
    EditorBase(parent),
    ui(new Ui::MailFilter)
{
    ui->setupUi(this);
}

MailFilter::~MailFilter()
{
    delete ui;
}

void MailFilter::save(std::shared_ptr<Database>)
{

}

void MailFilter::save_as(std::shared_ptr<Database>)
{

}

