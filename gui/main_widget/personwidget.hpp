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

private slots:
    void on_surname_edit_textChanged(const QString);
    void on_name_edit_textChanged(const QString);
    void paintEvent(QPaintEvent *);
    void on_add_event_button_clicked();
    void on_remove_event_button_clicked();
    void on_remove_category_button_clicked();

    void on_add_category_button_clicked();

private:
    std::shared_ptr<Database> _db;
    Ui::PersonWidget *ui;
};

#endif // PERSONWIDGET_HPP
