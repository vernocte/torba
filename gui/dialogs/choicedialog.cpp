#include "choicedialog.hpp"
#include "ui_choicedialog.h"

ChoiceDialog::ChoiceDialog(const QString& message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiceDialog)
{
    ui->setupUi(this);
    ui->message_label->setText(message);
}

ChoiceDialog::~ChoiceDialog()
{
    delete ui;
}

void ChoiceDialog::on_ok_button_clicked()
{
    QDialog::accept();
}

void ChoiceDialog::on_cancel_button_clicked()
{
    QDialog::reject();
}
