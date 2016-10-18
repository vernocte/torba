#ifndef MESSAGEDIALOG_HPP
#define MESSAGEDIALOG_HPP

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(const QString &message, QWidget *parent = 0);
    ~MessageDialog();

private slots:
    void on_ok_button_clicked();

private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOG_HPP
