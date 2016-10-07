#include "bottombar.hpp"
#include "ui_bottombar.h"

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::display(QString msg, bool err)
{

    ui->message->setStyleSheet((err) ? "color: red;" : "color: green;");
    ui->message->setText(msg);
}
