#include "personwidget.hpp"
#include "ui_personwidget.h"

#include "../dialogs/messagedialog.hpp"
#include "../dialogs/openeventdialog.hpp"
#include "../../backend/entities/evententity.hpp"
#include "../subwidgets/eventattendancewidget.hpp"
#include "../dialogs/categorydialog.hpp"
#include "../dialogs/choicedialog.hpp"

#include <QPainter>

PersonWidget::PersonWidget(std::shared_ptr<Database> db, PersonEntity p, QWidget *parent) :
    EditorBase(parent), _db(db),
    ui(new Ui::PersonWidget)
{
    ui->setupUi(this);
    ui->number_label->setText(QString::number(p.idx()));
    ui->name_edit->setText(p.name());
    ui->surname_edit->setText(p.surname());
    ui->birth_date_edit->setDate(p.birthday());
    ui->mail_edit->setText(p.email());
    ui->phone_edit->setText(p.phone());
    ui->place_edit->setText(p.birthplace());
    ui->comments_edit->setPlainText(p.comment());
    ui->postal_number_edit->setValue(p.postal_number());
    ui->post_edit->setText(p.post());
    ui->sex_combobox->setCurrentIndex(p.sex()?1:0);
    ui->street_edit->setText(p.street());
    ui->street_number_edit->setText(p.street_number());
    ui->country_edit->setText(p.country());
    for(auto it=p.lead().begin(); it!=p.lead().end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        ui->events_list->addItem(item);
        ui->events_list->setItemWidget(item, new EventAttendanceWidget(*it, true, ui->events_list));
    }
    for(auto it=p.participated().begin(); it!=p.participated().end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        ui->events_list->addItem(item);
        ui->events_list->setItemWidget(item, new EventAttendanceWidget(*it, false, ui->events_list));
    }

    for(auto it=p.roles().begin(); it!=p.roles().end(); ++it)
    {
        ui->role_list->addItem(*it);
    }
    _dirty = false;
}

PersonWidget::~PersonWidget()
{
    delete ui;
}

void PersonWidget::on_surname_edit_textChanged(const QString)
{
    if(ui->surname_edit->text()=="")
    {
        ui->surname_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid rgb(113, 10, 6);"
        );
    }
    else
    {
        ui->surname_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }
    dirty(true);
}

void PersonWidget::on_name_edit_textChanged(const QString)
{
    if(ui->name_edit->text()=="")
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid rgb(113, 10, 6);"
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

void PersonWidget::save_as()
{
    if(ui->name_edit->text()=="" || ui->surname_edit->text()=="") return;
    ChoiceDialog message("Oseba bo shranjena pod novo številko, spremembe na originalni osebi ne bodo shranjene!");
    if(message.exec())
    {
        ui->number_label->setText(0);
        save();
    }
}

void PersonWidget::save()
{
    if(ui->name_edit->text()=="" || ui->surname_edit->text()=="") return;
    PersonEntity p;
    p.idx(ui->number_label->text().toInt());
    p.name(ui->name_edit->text());
    p.surname(ui->surname_edit->text());
    p.birthday(ui->birth_date_edit->date());
    p.birthplace(ui->place_edit->text());
    p.comment(ui->comments_edit->toPlainText());
    p.country(ui->country_edit->text());
    p.email(ui->mail_edit->text());
    p.phone(ui->phone_edit->text());
    p.post(ui->post_edit->text());
    p.postal_number(ui->postal_number_edit->value());
    p.sex(ui->sex_combobox->currentIndex()==1);
    p.street(ui->street_edit->text());
    p.street_number(ui->street_number_edit->text());
    for(int i=0; i<ui->events_list->count(); ++i)
    {
        std::pair<int, bool> attendance = ((EventAttendanceWidget*)ui->events_list->itemWidget(ui->events_list->item(i)))->get();
        if(attendance.second) p.lead().emplace_back(EventBaseEntity(attendance.first));
        else p.participated().emplace_back(EventBaseEntity(attendance.first));
    }
    for(int i=0; i<ui->role_list->count(); ++i)
    {
        p.roles().emplace_back(ui->role_list->item(i)->text());
    }

    if(p.idx()==0)
    {
        ui->number_label->setText(QString::number(_db->insert_person(p)));
        if(ui->number_label->text().toInt()==0)
        {
            MessageDialog message("Napaka pri shranjevanju, oseba ni shranjena! Preverite, če je baza odprta v drugem programu!");
            message.exec();
        }
        else
        {
            MessageDialog message("Oseba uspešno shranjena!");
            message.exec();
        }
    }
    else
    {
        try
        {
            _db->save_person(p);
            MessageDialog message("Podatki o osebi uspešno posodobljeni!");
            message.exec();
        }
        catch(std::logic_error&)
        {
            MessageDialog message("Napaka pri shranjevanju, oseba ni shranjena! Preverite, če je baza odprta v drugem programu!");
            message.exec();
        }
    }
    QString text = ui->name_edit->text() + " " + ui->surname_edit->text();
    emit base_text(text);
    dirty(false);
}

void PersonWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PersonWidget::on_add_event_button_clicked()
{
    if(_db!=NULL)
    {
        OpenEventDialog e(_db);
        if(e.exec())
        {
            std::vector<EventEntity> events = e.event();
            for(auto it = events.begin(); it!=events.end(); ++it)
            {
                emit add_person(it->idx(), PersonBaseEntity(ui->number_label->text().toInt(), ui->name_edit->text(), ui->surname_edit->text()), false);
                QListWidgetItem *item = new QListWidgetItem();
                item->setSizeHint(QSize(item->sizeHint().width(), 30));
                ui->events_list->addItem(item);
                ui->events_list->setItemWidget(item, new EventAttendanceWidget(*it, false, ui->events_list));
            }
            dirty(true);
        }
    }
}

void PersonWidget::on_remove_event_button_clicked()
{
    if(!ui->events_list->selectedItems().empty())
    {
        for(int i=0; i<ui->events_list->selectedItems().count(); ++i)
        {
            emit remove_person(((EventAttendanceWidget*)ui->events_list->itemWidget(ui->events_list->selectedItems()[i]))->get().first,
                               ui->number_label->text().toInt(), ((EventAttendanceWidget*)ui->events_list->itemWidget(ui->events_list->selectedItems()[i]))->get().second);
        }
        qDeleteAll(ui->events_list->selectedItems());
        dirty(true);
    }
}

void PersonWidget::on_remove_category_button_clicked()
{
    if(!ui->role_list->selectedItems().empty())
    {
        qDeleteAll(ui->role_list->selectedItems());
        dirty(true);
    }
}

QColor PersonWidget::color()
{
    return QColor(113, 10, 6);
}

void PersonWidget::on_add_category_button_clicked()
{
    CategoryDialog c(_db);
    if(c.exec())
    {
        ui->role_list->addItems(c.selected());
        dirty(true);
    }
}

QString PersonWidget::type()
{
    return "person";
}
int PersonWidget::idx()
{
    return ui->number_label->text().toInt();
}

bool PersonWidget::dirty()
{
    return _dirty;
}

void PersonWidget::dirty(bool val)
{
    if(_dirty!=val)
    {
        _dirty = val;
        emit dirty_changed(_dirty);
    }
}

void PersonWidget::on_sex_combobox_currentIndexChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_street_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_street_number_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_postal_number_edit_valueChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_post_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_country_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_birth_date_edit_dateChanged(const QDate &)
{
    dirty(true);
}

void PersonWidget::on_place_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_phone_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_mail_edit_textChanged(const QString &)
{
    dirty(true);
}

void PersonWidget::on_comments_edit_textChanged()
{
    dirty(true);
}

void PersonWidget::add_event(const EventBaseEntity& e, bool leader)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(item->sizeHint().width(), 30));
    ui->events_list->addItem(item);
    ui->events_list->setItemWidget(item, new EventAttendanceWidget(e, leader, ui->events_list));

    dirty(true);
}

void PersonWidget::remove_event(int idx)
{
    for(int i=0; i<ui->events_list->count(); ++i)
    {
        if(((EventAttendanceWidget*)ui->events_list->itemWidget(ui->events_list->item(i)))->get().first == idx)
        {
            delete ui->events_list->itemWidget(ui->events_list->item(i));
            delete ui->events_list->takeItem(i);
        }
    }

}
