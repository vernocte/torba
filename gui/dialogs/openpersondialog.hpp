#ifndef OPENPERSONDIALOG_HPP
#define OPENPERSONDIALOG_HPP

#include <QDialog>
#include <vector>

#include "../../backend/entities/personbaseentity.hpp"
#include "../../backend/entities/personentity.hpp"
#include "../../backend/database.hpp"

namespace Ui {
class OpenPersonDialog;
}

class OpenPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenPersonDialog(Database &db, QWidget *parent = 0);
    ~OpenPersonDialog();

public slots:
    std::vector<PersonEntity> person();
    std::vector<int> index();

private slots:
    void on_open_button_clicked();
    void on_cancel_button_clicked();
    void on_new_button_clicked();

    void on_filter_edit_textChanged(const QString &arg1);

private:
    Ui::OpenPersonDialog *ui;
    std::vector<PersonBaseEntity> _val;
    Database& _db;
    QStringList _persons;
};

#endif // OPENPERSONDIALOG_HPP
