#ifndef MAILFILTER_HPP
#define MAILFILTER_HPP

#include <QWidget>
#include "editorbase.hpp"

namespace Ui {
class MailFilter;
}

class MailFilter : public EditorBase
{
    Q_OBJECT

public:
    explicit MailFilter(QWidget *parent = 0);
    ~MailFilter();
    void save() override;
    void save_as() override;
    QColor color() override;

private:
    Ui::MailFilter *ui;
    void paintEvent(QPaintEvent *);
};

#endif // MAILFILTER_HPP
