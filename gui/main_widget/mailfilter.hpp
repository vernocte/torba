#ifndef MAILFILTER_HPP
#define MAILFILTER_HPP

#include <QWidget>
#include "editorbase.hpp"
#include "backend/entities/filterentity.hpp"

namespace Ui {
class MailFilter;
}

class MailFilter : public EditorBase
{
    Q_OBJECT

public:
    explicit MailFilter(std::shared_ptr<Database> db, QWidget *parent = 0);
    ~MailFilter();
    void save() override;
    void save_as() override;
    QColor color() override;
    virtual QString type() override;
    virtual int idx() override;
    virtual bool dirty() override;

private slots:

    void on_name_checkbox_clicked(bool checked);
    void on_address_checkbox_clicked(bool checked);
    void on_mail_checkbox_clicked(bool checked);
    void on_birth_date_checkbox_clicked(bool checked);
    void on_birth_place_checkbox_clicked(bool checked);
    void on_visited_group_clicked(bool checked);
    void on_event_type_clicked(bool checked);
    void on_category_clicked(bool checked);
    void on_add_event_button_clicked();
    void on_remove_event_button_clicked();
    void on_events_group_clicked(bool checked);
    void on_visited_from_edit_editingFinished();
    void on_visited_to_edit_editingFinished();
    void on_event_type_box_currentIndexChanged(const QString &);
    void on_category_box_currentIndexChanged(const QString &arg1);
    void on_date_of_birth_clicked(bool checked);
    void on_birth_from_date_editingFinished();
    void on_birth_to_date_editingFinished();
    void on_export_mail_button_clicked();

private:

    std::shared_ptr<Database> _db;
    std::vector<PersonEntity> _people;
    FilterEntity _filter;
    Ui::MailFilter *ui;
    void paintEvent(QPaintEvent *);
    void filter_events();
    void update_selection();
};

#endif // MAILFILTER_HPP
