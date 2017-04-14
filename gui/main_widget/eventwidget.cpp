#include "eventwidget.hpp"
#include "ui_eventwidget.h"

#include <string>

#include <QPainter>

#include "../dialogs/messagedialog.hpp"
#include "../dialogs/openpersondialog.hpp"
#include "../dialogs/choicedialog.hpp"

EventWidget::EventWidget(std::shared_ptr<Database> db, EventEntity e, QWidget *parent) :
    EditorBase(parent),
    ui(new Ui::EventWidget), _db(db)
{
    ui->setupUi(this);
    ui->comments_edit->setPlainText(e.comment());
    ui->from_edit->setDate(e.start_date());
    ui->number_label->setText(QString::number(e.idx()));
    ui->name_edit->setText(e.name());
    ui->to_edit->setDate(e.end_date());
    ui->type_edit->setText(e.type());
    for(auto it=e.leaders().begin(); it!=e.leaders().end(); ++it)
    {
        ui->leaders_list->addItem(QString::number(it->idx()) + "\t" + it->name() + "\t" + it->surname());
    }
    for(auto it=e.participants().begin(); it!=e.participants().end(); ++it)
    {
        ui->participants_list->addItem(QString::number(it->idx()) + "\t" + it->name() + "\t" + it->surname());
    }
    dirty(false);
}

EventWidget::~EventWidget()
{
    delete ui;
}

void EventWidget::on_name_edit_textChanged(const QString)
{
    if(ui->name_edit->text()=="")
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid rgb(23,43,104);"
        );
    }
    else
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }
    dirty(true);
}

void EventWidget::on_type_edit_textChanged(const QString)
{
    if(ui->type_edit->text()=="")
    {
        ui->type_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid rgb(23,43,104);"
        );
    }
    else
    {
        ui->type_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }
    dirty(true);
}

void EventWidget::save()
{
    if(ui->name_edit->text() == "" || ui->type_edit->text() == "") return;
    EventEntity e;
    e.idx(ui->number_label->text().toInt());
    e.name(ui->name_edit->text());
    e.type(ui->type_edit->text());
    e.start_date(ui->from_edit->date());
    e.end_date(ui->to_edit->date());
    e.comment(ui->comments_edit->toPlainText());
    for(int i=0; i<ui->participants_list->count(); ++i)
    {
        PersonBaseEntity p;
        p.idx(std::stoi(ui->participants_list->item(i)->text().toStdString()));
        e.participants().emplace_back(p);
    }
    for(int i=0; i<ui->leaders_list->count(); ++i)
    {
        PersonBaseEntity p;
        p.idx(std::stoi(ui->leaders_list->item(i)->text().toStdString()));
        e.leaders().emplace_back(p);
    }

    if(e.idx()==0)
    {
        ui->number_label->setText(QString::number(_db->insert_event(e)));
        if(ui->number_label->text().toInt()==0)
        {
            MessageDialog message("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!");
            message.exec();
        }
        else
        {
            MessageDialog message("Dogodek uspešno shranjen!");
            message.exec();
        }
    }
    else
    {
        try
        {
            _db->save_event(e);
            MessageDialog message("Podatki o dogodku uspešno posodobljeni!");
            message.exec();
        }
        catch(std::logic_error&)
        {
            MessageDialog message("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!");
            message.exec();
        }
    }
    dirty(false);
    QString text = ui->name_edit->text() + " " + ui->type_edit->text();
    emit base_text(text);

}

void EventWidget::save_as()
{
    if(ui->name_edit->text() == "" || ui->type_edit->text() == "") return;
    ChoiceDialog message("Dogodek bo shranjen pod novo številko, spremembe na originalnem dogodku ne bodo shranjene!");
    if(message.exec())
    {
        ui->number_label->setText(0);
        save();
    }
}

void EventWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QColor EventWidget::color()
{
    return QColor(23,43,104);
}

void EventWidget::on_add_participant_button_clicked()
{
    std::vector<PersonEntity> persons;
    OpenPersonDialog p(_db, true);
    if(p.exec())
    {
        persons = p.person();
    }
    if(persons.size()==1 && persons[0].idx()==0)
    {
        persons[0].participated().emplace_back(EventBaseEntity(ui->number_label->text().toInt(), ui->name_edit->text(),ui->type_edit->text()));
        emit open_new_person(persons[0]);
    }
    for(auto it = persons.begin(); it!=persons.end(); ++it)
    {
        emit add_event(it->idx(), EventBaseEntity(ui->number_label->text().toInt(), ui->name_edit->text(), ui->type_edit->text()), false);
        ui->participants_list->addItem(QString::number(it->idx()) + "\t" + it->name() + "\t" + it->surname());
        dirty(true);
    }
}

void EventWidget::on_remove_person_button_clicked()
{
    if(!ui->participants_list->selectedItems().empty())
    {
        for(int i=0; i<ui->participants_list->selectedItems().count(); ++i)
        {
            emit remove_event(std::stoi(ui->participants_list->selectedItems()[i]->text().toStdString()), ui->number_label->text().toInt());
        }
        qDeleteAll(ui->participants_list->selectedItems());
        dirty(true);
    }
}

void EventWidget::on_remove_leader_button_clicked()
{
    if(!ui->leaders_list->selectedItems().empty())
    {
        for(int i=0; i<ui->participants_list->selectedItems().count(); ++i)
        {
            emit remove_event(std::stoi(ui->participants_list->selectedItems()[i]->text().toStdString()), ui->number_label->text().toInt());
        }
        qDeleteAll(ui->leaders_list->selectedItems());
        dirty(true);
    }
}

void EventWidget::on_add_leader_button_clicked()
{
    std::vector<PersonEntity> persons;
    OpenPersonDialog p(_db, true);
    if(p.exec())
    {
        persons = p.person();
    }
    if(persons.size()==1 && persons[0].idx()==0)
    {
        persons[0].lead().emplace_back(EventBaseEntity(ui->number_label->text().toInt(), ui->name_edit->text(),ui->type_edit->text()));
        emit open_new_person(persons[0]);
    }
    for(auto it = persons.begin(); it!=persons.end(); ++it)
    {
        emit add_event(it->idx(), EventBaseEntity(ui->number_label->text().toInt(), ui->name_edit->text(), ui->type_edit->text()), true);
        ui->leaders_list->addItem(QString::number(it->idx()) + "\t" + it->name() + "\t" + it->surname());
        dirty(true);
    }
}


QString EventWidget::type()
{
    return "event";
}
int EventWidget::idx()
{
    return ui->number_label->text().toInt();
}
bool EventWidget::dirty()
{
    return _dirty;
}

void EventWidget::dirty(bool val)
{
    if(_dirty!=val)
    {
        _dirty = val;
        emit dirty_changed(_dirty);
    }
}

void EventWidget::on_from_edit_dateChanged(const QDate &)
{
    dirty(true);
}

void EventWidget::on_to_edit_dateChanged(const QDate &)
{
    dirty(true);
}

void EventWidget::on_comments_edit_textChanged()
{
    dirty(true);
}

void EventWidget::add_person(const PersonBaseEntity& p, bool leader)
{
    if(leader)
    {
        ui->leaders_list->addItem(QString::number(p.idx()) + "\t" + p.name() + "\t" + p.surname());
    }
    else
    {
        ui->participants_list->addItem(QString::number(p.idx()) + "\t" + p.name() + "\t" + p.surname());
    }
    dirty(true);
}

void EventWidget::remove_person(int idx, bool leader)
{
    if(leader)
    {
        for(int i=0; i<ui->leaders_list->count(); ++i)
        {
            if(std::stoi(ui->leaders_list->item(i)->text().toStdString()) == idx)
            {
                delete ui->leaders_list->takeItem(i);
            }
        }
    }
    else
    {
        for(int i=0; i<ui->participants_list->count(); ++i)
        {
            if(std::stoi(ui->participants_list->item(i)->text().toStdString()) == idx)
            {
                delete ui->participants_list->takeItem(i);
            }
        }
    }
}
