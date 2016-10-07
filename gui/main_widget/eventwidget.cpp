#include "eventwidget.hpp"
#include "ui_eventwidget.h"

#include <QMessageBox>

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

void EventWidget::save(Database &db)
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
        ui->number_label->setText(QString::number(db.insert_event(e)));
        if(ui->number_label->text().toInt()==0)
        {
            QMessageBox message;
            message.setText("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
        else
        {
            QMessageBox message;
            message.setText("Dogodek uspešno shranjen!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
    }
    else
    {
        if(db.save_event(e))
        {
            QMessageBox message;
            message.setText("Podatki o dogodku uspešno posodobljeni!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
        else
        {
            QMessageBox message;
            message.setText("Napaka pri shranjevanju, dogodek ni shranjen! Preverite, če je baza odprta v drugem programu!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
    }
}

void EventWidget::save_as(Database &db)
{
    if(ui->name_edit->text() == "" || ui->type_edit->text() == "") return;
    QMessageBox message;
    message.setText("Dogodek bo shranjen pod novo številko, spremembe na originalnem dogodku ne bodo shranjene!");
    message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                          "QMessageBox QLabel { color: white; }"
                          "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:12px;}");
    message.exec();
    ui->number_label->setText(0);
    save(db);
}
