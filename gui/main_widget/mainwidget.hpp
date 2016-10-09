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
   void save(std::shared_ptr<Database> &db);
   void save_as(std::shared_ptr<Database> &db);
   void save_all(std::shared_ptr<Database> &db);
   void open_person(const PersonEntity& p);
   void open_event(const EventEntity& e);

private slots:
    void close_file(int index);
    void change_text(QString val);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_HPP
