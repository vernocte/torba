#include "mailfilter.hpp"
#include "ui_mailfilter.h"
#include <QPainter>

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

void MailFilter::save()
{

}

void MailFilter::save_as()
{

}

void MailFilter::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QColor MailFilter::color()
{
    return Qt::yellow;
}
