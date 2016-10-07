#include "personwidget.hpp"
#include "ui_personwidget.h"

#include <QMessageBox>

PersonWidget::PersonWidget(PersonEntity p, QWidget *parent) :
    EditorBase(parent),
    ui(new Ui::PersonWidget)
{
    ui->setupUi(this);
    ui->number_label->setText(QString::number(p.idx()));
    ui->name_edit->setText(p.name());
    if(p.name() == "")
    {
        ui->name_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid red;"
        );
    }
    ui->surname_edit->setText(p.surname());
    if(p.surname() == "")
    {
        ui->surname_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
                "border: 2px solid red;"
        );
    }
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
                "border: 2px solid red;"
        );
    }
    else
    {
        ui->surname_edit->setStyleSheet("color: white;"
                "background-color: rgb(40,40,40);"
        );
    }

    QString text = ui->name_edit->text() + " " + ui->surname_edit->text();
    emit base_text(text);
}

void PersonWidget::on_name_edit_textChanged(const QString)
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
    QString text = ui->name_edit->text() + " " + ui->surname_edit->text();
    emit base_text(text);
}

void PersonWidget::save_as(Database& db)
{
    if(ui->name_edit->text()=="" || ui->surname_edit->text()=="") return;
    QMessageBox message;
    message.setText("Oseba bo shranjena pod novo številko, spremembe na originalni osebi ne bodo shranjene!");
    message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                          "QMessageBox QLabel { color: white; }"
                          "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:12px;}");
    message.exec();
    ui->number_label->setText(0);
    save(db);
}

void PersonWidget::save(Database& db)
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

    if(p.idx()==0)
    {
        ui->number_label->setText(QString::number(db.insert_person(p)));
        if(ui->number_label->text().toInt()==0)
        {
            QMessageBox message;
            message.setText("Napaka pri shranjevanju, oseba ni shranjena! Preverite, če je baza odprta v drugem programu!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
        else
        {
            QMessageBox message;
            message.setText("Oseba uspešno shranjena!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
    }
    else
    {
        if(db.save_person(p))
        {
            QMessageBox message;
            message.setText("Podatki o osebi uspešno posodobljeni!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
        else
        {
            QMessageBox message;
            message.setText("Napaka pri shranjevanju, oseba ni shranjena! Preverite, če je baza odprta v drugem programu!");
            message.setStyleSheet("QMessageBox { color: white; background-color: rgb(80,80,80); }"
                                  "QMessageBox QLabel { color: white; }"
                                  "QMessageBox QPushButton { background-color: rgb(60,60,60); border: none; outline: none; padding:6px; }");
            message.exec();
        }
    }
}
