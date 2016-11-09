#ifndef CHOICEDIALOG_HPP
#define CHOICEDIALOG_HPP

#include <QDialog>

namespace Ui {
class ChoiceDialog;
}

class ChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiceDialog(const QString &message, QWidget *parent = 0);
    ~ChoiceDialog();

private slots:
    void on_ok_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::ChoiceDialog *ui;
};

#endif // CHOICEDIALOG_HPP
