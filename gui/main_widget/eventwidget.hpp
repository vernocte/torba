#ifndef EVENTWIDGET_HPP
#define EVENTWIDGET_HPP

#include <QWidget>
#include "editorbase.hpp"

#include "../../backend/entities/evententity.hpp"

namespace Ui {
class EventWidget;
}

class EventWidget : public EditorBase
{
    Q_OBJECT

public:
    explicit EventWidget(std::shared_ptr<Database> db, EventEntity e = EventEntity(), QWidget *parent = 0);
    ~EventWidget();
    void save() override;
    void save_as() override;
    QColor color() override;

signals:
    void open_new_person(const PersonEntity&);

private slots:
    void on_name_edit_textChanged(const QString);
    void on_type_edit_textChanged(const QString);
    void paintEvent(QPaintEvent *);
    void on_add_participant_button_clicked();
    void on_remove_person_button_clicked();
    void on_remove_leader_button_clicked();
    void on_add_leader_button_clicked();

private:
    Ui::EventWidget *ui;
    std::shared_ptr<Database> _db;
};

#endif // EVENTWIDGET_HPP
