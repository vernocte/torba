#ifndef PERSONWIDGET_HPP
#define PERSONWIDGET_HPP

#include <QWidget>
#include "editorbase.hpp"

#include "../../backend/entities/personentity.hpp"

namespace Ui {
class PersonWidget;
}

class PersonWidget : public EditorBase
{
    Q_OBJECT

public:
    explicit PersonWidget(PersonEntity p = PersonEntity(), QWidget *parent = 0);
    ~PersonWidget();
    void save(std::shared_ptr<Database> db) override;
    void save_as(std::shared_ptr<Database> db) override;

private slots:
    void on_surname_edit_textChanged(const QString);
    void on_name_edit_textChanged(const QString);

private:
    Ui::PersonWidget *ui;
};

#endif // PERSONWIDGET_HPP
