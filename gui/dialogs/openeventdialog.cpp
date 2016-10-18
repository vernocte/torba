#include "openeventdialog.hpp"
#include "ui_openeventdialog.h"

OpenEventDialog::OpenEventDialog(std::shared_ptr<Database> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenEventDialog), _db(db)
{
    ui->setupUi(this);
    std::vector<EventBaseEntity> events =  _db->event_list();
    for(uint i=0; i<events.size(); ++i)
    {
        _events.append(QString::number(events[i].idx()) + "\t" + events[i].name() + "\t" + events[i].type());
    }
    ui->event_list->addItems(_events);
}

OpenEventDialog::~OpenEventDialog()
{
    delete ui;
}

void OpenEventDialog::on_cancel_button_clicked()
{
    QDialog::reject();
}

void OpenEventDialog::on_open_button_clicked()
{
    QDialog::accept();
}

std::vector<EventEntity> OpenEventDialog::event()
{
    int len = ui->event_list->selectedItems().count();
    std::vector<EventEntity> res(len);
    for(int i=0; i<len; ++i)
    {
        res[i] = _db->get_event(std::stoi(ui->event_list->selectedItems()[i]->text().toStdString()));
    }
    return res;
}

std::vector<int> OpenEventDialog::index()
{
    int len = ui->event_list->selectedItems().count();
    std::vector<int> res(len);
    for(int i=0; i<len; ++i)
    {
        res[i] = std::stoi(ui->event_list->selectedItems()[i]->text().toStdString());
    }
    return res;
}

void OpenEventDialog::on_filter_edit_textChanged(const QString &arg1)
{
    QRegExp regex(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->event_list->clear();
    ui->event_list->addItems(_events.filter(regex));
}
