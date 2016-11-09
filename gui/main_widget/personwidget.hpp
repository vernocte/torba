#ifndef PERSONWIDGET_HPP
#define PERSONWIDGET_HPP

#include <QWidget>
#include <QPaintEvent>
#include "editorbase.hpp"

#include "../../backend/entities/personentity.hpp"
#include "../../backend/database.hpp"

namespace Ui {
class PersonWidget;
}

class PersonWidget : public EditorBase
{
    Q_OBJECT

public:
    explicit PersonWidget(std::shared_ptr<Database> db, PersonEntity p = PersonEntity(), QWidget *parent = 0);
    ~PersonWidget();
    void save() override;
    void save_as() override;
    QColor color() override;
    virtual QString type() override;
    virtual int idx() override;
    virtual bool dirty() override;
    void add_event(const EventBaseEntity& e, bool leader);
    void remove_event(int idx);

signals:
    void dirty_changed(bool);

    void add_person(int, const PersonBaseEntity&, bool);
    void remove_person(int, int, bool);

private slots:
    void on_surname_edit_textChanged(const QString);
    void on_name_edit_textChanged(const QString);
    void paintEvent(QPaintEvent *);
    void on_add_event_button_clicked();
    void on_remove_event_button_clicked();
    void on_remove_category_button_clicked();
    void on_add_category_button_clicked();
    void dirty(bool val);
    void on_sex_combobox_currentIndexChanged(const QString &);
    void on_street_edit_textChanged(const QString &);
    void on_street_number_edit_textChanged(const QString &);
    void on_postal_number_edit_valueChanged(const QString &);
    void on_post_edit_textChanged(const QString &);
    void on_country_edit_textChanged(const QString &);
    void on_birth_date_edit_dateChanged(const QDate &);
    void on_place_edit_textChanged(const QString &);
    void on_phone_edit_textChanged(const QString &);
    void on_mail_edit_textChanged(const QString &);
    void on_comments_edit_textChanged();

private:
    std::shared_ptr<Database> _db;
    Ui::PersonWidget *ui;
    bool _dirty;
};

#endif // PERSONWIDGET_HPP
