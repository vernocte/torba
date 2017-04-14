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
    virtual QString type() override;
    virtual int idx() override;
    virtual bool dirty() override;

    void add_person(const PersonBaseEntity& p, bool leader);
    void remove_person(int idx, bool leader);

signals:
    void open_new_person(const PersonEntity&);
    void dirty_changed(bool);


    void add_event(int, const EventBaseEntity&, bool);
    void remove_event(int, int);

private slots:
    void on_name_edit_textChanged(const QString);
    void on_type_edit_textChanged(const QString);
    void paintEvent(QPaintEvent *);
    void on_add_participant_button_clicked();
    void on_remove_person_button_clicked();
    void on_remove_leader_button_clicked();
    void on_add_leader_button_clicked();
    void dirty(bool val);
    void on_from_edit_dateChanged(const QDate &);
    void on_to_edit_dateChanged(const QDate &);
    void on_comments_edit_textChanged();

private:
    Ui::EventWidget *ui;
    std::shared_ptr<Database> _db;
    bool _dirty;
};

#endif // EVENTWIDGET_HPP
