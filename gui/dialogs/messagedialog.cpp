#include "messagedialog.hpp"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(const QString& message, const QString& title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    ui->message_label->setText(message);
    setWindowTitle(title);

}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_ok_button_clicked()
{
    accept();
}
