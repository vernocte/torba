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
    explicit EventWidget(EventEntity e = EventEntity(), QWidget *parent = 0);
    ~EventWidget();
    void save(std::shared_ptr<Database> db) override;
    void save_as(std::shared_ptr<Database> db) override;

private slots:
    void on_name_edit_textChanged(const QString);
    void on_type_edit_textChanged(const QString);

private:
    Ui::EventWidget *ui;
};

#endif // EVENTWIDGET_HPP
