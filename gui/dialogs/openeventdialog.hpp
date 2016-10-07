#ifndef OPENEVENTDIALOG_HPP
#define OPENEVENTDIALOG_HPP

#include <QDialog>
#include "../../backend/entities/eventbaseentity.hpp"
#include "../../backend/database.hpp"

namespace Ui {
class OpenEventDialog;
}

class OpenEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenEventDialog(Database& db, QWidget *parent = 0);
    ~OpenEventDialog();

private slots:
    void on_cancel_button_clicked();
    void on_open_button_clicked();
    void on_filter_edit_textChanged(const QString &arg1);

public slots:
    std::vector<EventEntity> event();
    std::vector<int> index();

private:
    Ui::OpenEventDialog *ui;
    QStringList _events;
    Database& _db;
};

#endif // OPENEVENTDIALOG_HPP
