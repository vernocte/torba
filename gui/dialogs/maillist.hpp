#ifndef MAILLIST_HPP
#define MAILLIST_HPP

#include <QDialog>
#include <QString>

namespace Ui {
class MailList;
}

class MailList : public QDialog
{
    Q_OBJECT

public:
    explicit MailList(const QString& text, QWidget *parent = 0);
    ~MailList();

private:
    Ui::MailList *ui;
};

#endif // MAILLIST_HPP
