#ifndef CATEGORYDIALOG_HPP
#define CATEGORYDIALOG_HPP

#include <QDialog>
#include <memory>
#include "../../backend/database.hpp"

namespace Ui {
class CategoryDialog;
}

class CategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryDialog(std::shared_ptr<Database> &db, QWidget *parent = 0);
    ~CategoryDialog();
    QStringList selected();

private slots:
    void on_filter_edit_textChanged(const QString &arg1);
    void on_cancel_button_clicked();
    void on_ok_button_clicked();
    void on_add_button_clicked();

private:
    Ui::CategoryDialog *ui;
    QStringList _categories;
    std::shared_ptr<Database> _db;
};

#endif // CATEGORYDIALOG_HPP
