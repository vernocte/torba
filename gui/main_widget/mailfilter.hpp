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
    void save(Database&) override;
    void save_as(Database&) override;

private:
    Ui::MailFilter *ui;
};

#endif // MAILFILTER_HPP
