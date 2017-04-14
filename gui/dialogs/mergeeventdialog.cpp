#include "mergeeventdialog.hpp"
#include "ui_mergeeventdialog.h"

MergeEventDialog::MergeEventDialog(const EventEntity &existing, const EventEntity &new_event, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MergeEventDialog)
{
    ui->setupUi(this);
    ui->event_label->setText(existing.name() + " - " + existing.type());

    if(existing.start_date() != new_event.start_date())
    {
        ui->date_from_left->setText(existing.start_date().toString("dd.MM.yyyy"));
        ui->date_from_right->setText(new_event.start_date().toString("dd.MM.yyyy"));
    }
    else
    {
        ui->date_from_widget->hide();
    }

    if(existing.end_date() != new_event.end_date())
    {
        ui->date_to_left->setText(existing.end_date().toString("dd.MM.yyyy"));
        ui->date_to_right->setText(new_event.end_date().toString("dd.MM.yyyy"));
    }
    else
    {
        ui->date_to_widget->hide();
    }
    ui->comment_edit->setAcceptRichText(true);
    if(existing.comment() != new_event.comment())
    {
        ui->comment_edit->setText("<span style='colour: red'>" + existing.comment() + "</span><br><span style='colour: green'>" + new_event.comment() + "</span>");
    }
    else
    {
        ui->comment_edit->hide();
    }
    _event = new_event;
}

MergeEventDialog::~MergeEventDialog()
{
    delete ui;
}

EventEntity MergeEventDialog::get_event()
{
    return _event;
}

void MergeEventDialog::on_keep_both_button_clicked()
{
    _event.idx(0);
    QDialog::accept();

}

void MergeEventDialog::on_merge_button_clicked()
{
    if(ui->date_from_left->isChecked() && ui->date_from_widget->isVisible())
    {
        _event.start_date(QDate::fromString(ui->date_from_left->text(), "dd.MM.yyyy"));
    }
    if(ui->date_to_left->isChecked() && ui->date_to_widget->isVisible())
    {
        _event.end_date(QDate::fromString(ui->date_to_left->text(), "dd.MM.yyyy"));
    }
    if(ui->comment_edit->isVisible())
    {
        _event.comment(ui->comment_edit->toPlainText());
    }
    QDialog::accept();
}
