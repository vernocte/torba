#include "eventwidget.hpp"
#include "ui_eventwidget.h"

#include "../dialogs/messagedialog.hpp"

EventWidget::EventWidget(EventEntity e, QWidget *parent) :
    EditorBase(parent),
    ui(new Ui::EventWidget)
{
    ui->setupUi(this);
    ui->comments_edit->setPlainText(e.comment());
    ui->from_edit->setDate(e.start_date());
    ui->number_label->setText(QString::number(e.idx()));
    ui->name_edit->setText(e.name());
    if(e.name() == "")
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid red;"
        );
    }
    ui->to_edit->setDate(e.end_date());
    ui->type_edit->setText(e.type());
    if(e.type() == "")
    {
        ui->type_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid red;"
        );
    }
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
                "border: 2px solid red;"
        );
    }
    else
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }
    QString text = ui->name_edit->text() + " " + ui->type_edit->text();
    emit base_text(text);
}

void EventWidget::on_type_edit_textChanged(const QString)
{
    if(ui->type_edit->text()=="")
    {
        ui->type_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid red;"
        );
    }
    else
    {
        ui->type_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }
    QString text = ui->name_edit->text() + " " + ui->type_edit->text();
    emit base_text(text);
}

void EventWidget::save(std::shared_ptr<Database> db)
{
    if(ui->name_edit->text() == "" || ui->type_edit->text() == "") return;
    EventEntity e;
    e.idx(ui->number_label->text().toInt());
    e.name(ui->name_edit->text());
    e.type(ui->type_edit->text());
    e.start_date(ui->from_edit->date());
    e.end_date(ui->to_edit->date());

    if(e.idx()==0)
    {
        ui->number_label->setText(QString::number(db->insert_event(e)));
        if(ui->number_label->text().toInt()==0)
        {
            MessageDialog message("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!", "Napaka pri shranjevanju");
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
            db->save_event(e);
            MessageDialog message("Podatki o dogodku uspešno posodobljeni!");
            message.exec();
        }
        catch(std::logic_error&)
        {
            MessageDialog message("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!", "Napaka pri shranjevanju");
            message.exec();
        }
    }
}

void EventWidget::save_as(std::shared_ptr<Database> db)
{
    if(ui->name_edit->text() == "" || ui->type_edit->text() == "") return;
    MessageDialog message("Dogodek bo shranjen pod novo številko, spremembe na originalnem dogodku ne bodo shranjene!");
    message.exec();
    ui->number_label->setText(0);
    save(db);
}
