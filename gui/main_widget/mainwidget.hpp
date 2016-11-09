#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <memory>

#include <QWidget>

#include "../../backend/entities/personentity.hpp"
#include "../../backend/entities/evententity.hpp"
#include "../../backend/database.hpp"



namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
   void new_person(PersonEntity p = PersonEntity());
   void new_event(EventEntity e = EventEntity());
   void new_mail_filter();
   void save();
   void save_as();
   void save_all();
   void open_person(const PersonEntity& p);
   void open_event(const EventEntity& e);
   void database(std::shared_ptr<Database> db);

private slots:
    void close_file(int index);
    void change_text(QString val);
    void dirty(bool);
    void paintEvent(QPaintEvent *);

    // cross update
    void add_event(int idx, const EventBaseEntity& e, bool leader);
    void remove_event(int person, int event);
    void add_person(int event, const PersonBaseEntity p, bool leader);
    void remove_person(int event, int person, bool leader);

private:
    Ui::MainWidget *ui;
    std::shared_ptr<Database> _db;
};

#endif // MAINWIDGET_HPP
