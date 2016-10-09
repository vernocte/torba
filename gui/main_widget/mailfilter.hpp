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
    void save(std::shared_ptr<Database>) override;
    void save_as(std::shared_ptr<Database>) override;

private:
    Ui::MailFilter *ui;
};

#endif // MAILFILTER_HPP
