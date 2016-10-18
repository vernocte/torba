#include "eventattendancewidget.hpp"
#include "ui_eventattendancewidget.h"

EventAttendanceWidget::EventAttendanceWidget(const EventBaseEntity &e, bool leader, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventAttendanceWidget)
{
    ui->setupUi(this);
    ui->idx_label->setText(QString::number(e.idx()));
    ui->name_label->setText(e.name());
    ui->status_button->setChecked(leader);
    if(leader) ui->status_button->setText("Voditelj");
}

EventAttendanceWidget::~EventAttendanceWidget()
{
    delete ui;
}

void EventAttendanceWidget::on_status_button_clicked(bool checked)
{
    if(checked)
    {
        ui->status_button->setText("Voditelj");
    }
    else
    {
        ui->status_button->setText("Udeleženec");
    }
}

std::pair<int, bool> EventAttendanceWidget::get()
{
    return std::pair<int, bool>(ui->idx_label->text().toInt(), ui->status_button->isChecked());
}
