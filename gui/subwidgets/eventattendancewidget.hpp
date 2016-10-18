#ifndef EVENTATTENDANCEWIDGET_HPP
#define EVENTATTENDANCEWIDGET_HPP

#include <QWidget>
#include "../../backend/entities/eventbaseentity.hpp"

namespace Ui {
class EventAttendanceWidget;
}

class EventAttendanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventAttendanceWidget(const EventBaseEntity& e, bool leader, QWidget *parent = 0);
    ~EventAttendanceWidget();
    std::pair<int, bool> get();

private slots:

    void on_status_button_clicked(bool checked);

private:
    Ui::EventAttendanceWidget *ui;
};

#endif // EVENTATTENDANCEWIDGET_HPP
