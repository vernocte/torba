#include "categorydialog.hpp"
#include "ui_categorydialog.h"

CategoryDialog::CategoryDialog(std::shared_ptr<Database> &db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoryDialog)
{
    ui->setupUi(this);
    _db = db;

    _categories = _db->categories_list();
    ui->categories_list->addItems(_categories);
}

CategoryDialog::~CategoryDialog()
{
    delete ui;
}

void CategoryDialog::on_filter_edit_textChanged(const QString &arg1)
{
    QRegExp regex(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->categories_list->clear();
    ui->categories_list->addItems(_categories.filter(regex));
}

void CategoryDialog::on_cancel_button_clicked()
{
    QDialog::reject();
}

void CategoryDialog::on_ok_button_clicked()
{
    QDialog::accept();
}

void CategoryDialog::on_add_button_clicked()
{
    if(!_categories.contains(ui->filter_edit->text()))
    {
        _categories.append(ui->filter_edit->text());
        QRegExp regex(ui->filter_edit->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
        ui->categories_list->clear();
        ui->categories_list->addItems(_categories.filter(regex));
        _db->add_category(ui->filter_edit->text());
    }
}

QStringList CategoryDialog::selected()
{
    QStringList selections;
    auto categories = ui->categories_list->selectedItems();
    for(auto it=categories.begin(); it!=categories.end(); ++it)
    {
        selections.append((*it)->text());
    }
    return selections;
}
