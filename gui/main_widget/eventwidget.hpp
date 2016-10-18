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

private slots:
    void on_name_edit_textChanged(const QString);
    void on_type_edit_textChanged(const QString);
    void paintEvent(QPaintEvent *);

private:
    Ui::EventWidget *ui;
    std::shared_ptr<Database> _db;
};

#endif // EVENTWIDGET_HPP
