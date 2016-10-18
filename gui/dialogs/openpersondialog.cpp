#include "openpersondialog.hpp"
#include "ui_openpersondialog.h"

#include <QRegExp>

OpenPersonDialog::OpenPersonDialog(std::shared_ptr<Database> &db, bool allow_new, QWidget *parent) :
    QDialog(parent), ui(new Ui::OpenPersonDialog), _db(db), _persons()
{
    ui->setupUi(this);
    if(!allow_new) ui->new_button->hide();
    _val = _db->person_list();
    for(uint i=0; i<_val.size(); ++i)
    {
        _persons.append(QString::number(_val[i].idx()) + " " + _val[i].name() + " " + _val[i].surname());
    }
    ui->person_list->addItems(_persons);
}

OpenPersonDialog::~OpenPersonDialog()
{
    delete ui;
}

void OpenPersonDialog::on_open_button_clicked()
{
    QDialog::accept();
}

void OpenPersonDialog::on_cancel_button_clicked()
{
    QDialog::reject();
}

std::vector<PersonEntity> OpenPersonDialog::person()
{
    int len = ui->person_list->selectedItems().count();
    std::vector<PersonEntity> res(len);
    for(int i=0; i<len; ++i)
    {
        res[i] = _db->get_person(std::stoi(ui->person_list->selectedItems()[i]->text().toStdString()));
    }
    return res;
}

std::vector<int> OpenPersonDialog::index()
{
    int len = ui->person_list->selectedItems().count();
    std::vector<int> res(len);
    for(int i=0; i<len; ++i)
    {
        res[i] = std::stoi(ui->person_list->selectedItems()[i]->text().toStdString());
    }
    return res;
}

void OpenPersonDialog::on_new_button_clicked()
{
    ui->person_list->clear();
    ui->person_list->addItem("0");
    ui->person_list->setCurrentRow(0);
    QDialog::accept();
}

void OpenPersonDialog::on_filter_edit_textChanged(const QString &arg1)
{
    QRegExp regex(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->person_list->clear();
    ui->person_list->addItems(_persons.filter(regex));
}
