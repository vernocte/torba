#include "mergepersondialog.hpp"
#include "ui_mergepersondialog.h"

MergePersonDialog::MergePersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MergePersonDialog)
{
    ui->setupUi(this);
}

MergePersonDialog::~MergePersonDialog()
{
    delete ui;
}
