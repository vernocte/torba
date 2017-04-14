#ifndef MERGEEVENTDIALOG_HPP
#define MERGEEVENTDIALOG_HPP

#include <QDialog>

#include "backend/entities/evententity.hpp"

namespace Ui {
class MergeEventDialog;
}

class MergeEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MergeEventDialog(const EventEntity& existing, const EventEntity& new_event,  QWidget *parent = 0);
    ~MergeEventDialog();
    EventEntity get_event();

private slots:
    void on_keep_both_button_clicked();

    void on_merge_button_clicked();

private:
    Ui::MergeEventDialog *ui;
    EventEntity _event;
};

#endif // MERGEEVENTDIALOG_HPP
