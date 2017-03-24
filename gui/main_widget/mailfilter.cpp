#include "mailfilter.hpp"
#include "ui_mailfilter.h"
#include <QPainter>
#include "../dialogs/openeventdialog.hpp"
#include "../dialogs/maillist.hpp"
#include <string>

MailFilter::MailFilter(std::shared_ptr<Database> db, QWidget *parent)  :
    EditorBase(parent), _db(db), _filter(),
    ui(new Ui::MailFilter)
{
    ui->setupUi(this);
    ui->results_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->results_table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->results_table->verticalHeader()->setDefaultSectionSize(32);
    ui->category_box->insertItems(0, _db->categories_list());
    ui->event_type_box->insertItems(0, db->event_type_list());
    ui->results_table->setHorizontalHeaderLabels(QString("Ime in priimek;Naslov;Mail;Datum rojstva;Kraj rojstva").split(";"));
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
    return QColor(152,70,14);
}

QString MailFilter::type()
{
    return "filter";
}
int MailFilter::idx()
{
    return 0;
}

bool MailFilter::dirty()
{
    return false;
}

void MailFilter::on_name_checkbox_clicked(bool checked)
{
    if(!checked) ui->results_table->hideColumn(0);
    else ui->results_table->showColumn(0);
}

void MailFilter::on_address_checkbox_clicked(bool checked)
{
    if(!checked) ui->results_table->hideColumn(1);
    else ui->results_table->showColumn(1);
}

void MailFilter::on_mail_checkbox_clicked(bool checked)
{
    if(!checked) ui->results_table->hideColumn(2);
    else ui->results_table->showColumn(2);
}

void MailFilter::on_birth_date_checkbox_clicked(bool checked)
{
    if(!checked) ui->results_table->hideColumn(3);
    else ui->results_table->showColumn(3);
}

void MailFilter::on_birth_place_checkbox_clicked(bool checked)
{
    if(!checked) ui->results_table->hideColumn(4);
    else ui->results_table->showColumn(4);
}

void MailFilter::on_visited_group_clicked(bool checked)
{
    ui->visited_from_edit->setEnabled(checked);
    ui->visited_to_edit->setEnabled(checked);
    filter_events();
    update_selection();
}

void MailFilter::on_event_type_clicked(bool checked)
{
    ui->event_type_box->setEnabled(checked);
    filter_events();
    update_selection();
}

void MailFilter::on_category_clicked(bool checked)
{
    ui->category_box->setEnabled(checked);
    _filter.use_category(checked);
    update_selection();
}

void MailFilter::on_add_event_button_clicked()
{
    if(_db!=NULL)
    {
        OpenEventDialog e(_db);
        if(e.exec())
        {
            // FIXME does no checks for duplicates
            std::vector<EventEntity> events = e.event();
            for(auto it = events.begin(); it!=events.end(); ++it)
            {
                ui->event_list->addItem(QString::number(it->idx()) + '\t' + it->name() + '\t' + it->type());
                _filter.events().emplace_back(it->idx());
            }
        }
    }
    update_selection();
}

void MailFilter::on_remove_event_button_clicked()
{
    if(!ui->event_list->selectedItems().empty())
    {
        qDeleteAll(ui->event_list->selectedItems());
    }
    _filter.events().clear();
    for(int i=0; i<ui->event_list->count(); ++i)
    {
        _filter.events().emplace_back(std::stoi(ui->event_list->item(i)->text().toStdString()));
    }
    update_selection();
}

void MailFilter::on_events_group_clicked(bool checked)
{
    ui->add_event_button->setEnabled(checked);
    ui->remove_event_button->setEnabled(checked);
    filter_events();
    update_selection();
}

void MailFilter::on_visited_from_edit_editingFinished()
{
    filter_events();
    update_selection();
}

void MailFilter::on_visited_to_edit_editingFinished()
{
    filter_events();
    update_selection();
}

void MailFilter::on_event_type_box_currentIndexChanged(const QString &)
{
    filter_events();
    update_selection();
}

void MailFilter::filter_events()
{
    QDate start = (ui->visited_group->isChecked()) ? ui->visited_from_edit->date() : QDate(1900,1,1);
    QDate end = (ui->visited_group->isChecked()) ? ui->visited_to_edit->date() : QDate(2100,1,1);
    QString type = (ui->event_type->isChecked()) ? ui->event_type_box->currentText() : "";
    std::vector<EventBaseEntity> events = _db->events_between(start, end, type);
    ui->event_list->clear();
    _filter.events().clear();
    for(auto it = events.begin(); it!=events.end(); ++it)
    {
        ui->event_list->addItem(QString::number(it->idx()) + '\t' + it->name() + '\t' + it->type());
        _filter.events().emplace_back(it->idx());
    }
    _filter.use_events(ui->visited_group->isChecked() || ui->visited_group->isChecked() || ui->event_type->isChecked());
}

void MailFilter::update_selection()
{
    _people = _db->filter(_filter);
    ui->results_table->setRowCount(0);
    for(uint i=0; i<_people.size(); ++i)
    {
        ui->results_table->insertRow(i);

        QTableWidgetItem *name = new QTableWidgetItem(QString(_people[i].name() + " " + _people[i].surname()));
        ui->results_table->setItem(i,0, name);

        QString address_text = (_people[i].street()=="") ? "Ni naslova" : _people[i].street() + " " + _people[i].street_number() + "\n" +
                                                     QString::number(_people[i].postal_number()) + " " + _people[i].post();
        QTableWidgetItem *address = new QTableWidgetItem(address_text);
        ui->results_table->setItem(i,1, address);

        QString mail_text = (_people[i].email()=="") ? "Ni elektronskega naslova" : _people[i].email();
        QTableWidgetItem *mail = new QTableWidgetItem(mail_text);
        ui->results_table->setItem(i,2, mail);

        QString date_text = (_people[i].birthday()==QDate(1900,1,1)) ? "Ni rojstnega datuma" : _people[i].birthday().toString("dd.MM.yyyy");
        QTableWidgetItem *date = new QTableWidgetItem(date_text);
        ui->results_table->setItem(i,3, date);

        QString birthplace_text = (_people[i].birthplace()=="") ? "Ni rojstnega kraja" : _people[i].birthplace();
        QTableWidgetItem *birthplace = new QTableWidgetItem(birthplace_text);
        ui->results_table->setItem(i,4, birthplace);
    }

}

void MailFilter::on_category_box_currentIndexChanged(const QString &arg1)
{
    _filter.person_category(arg1);
    update_selection();
}

void MailFilter::on_date_of_birth_clicked(bool checked)
{
    ui->birth_to_date->setEnabled(checked);
    ui->birth_from_date->setEnabled(checked);
    _filter.born_from(ui->birth_from_date->date());
    _filter.born_to(ui->birth_to_date->date());
    _filter.use_birth(checked);
    update_selection();
}

void MailFilter::on_birth_from_date_editingFinished()
{
    _filter.born_from(ui->birth_from_date->date());
    update_selection();
}

void MailFilter::on_birth_to_date_editingFinished()
{
    _filter.born_to(ui->birth_to_date->date());
    update_selection();
}

void MailFilter::on_export_mail_button_clicked()
{
    QString mails;
    for(auto person : _people)
    {
        if(person.email()!="")
        {
            mails += person.email() + ";";
        }
    }
    MailList ml(mails);
    ml.exec();
}
