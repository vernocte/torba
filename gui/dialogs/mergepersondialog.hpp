#ifndef MERGEPERSONDIALOG_HPP
#define MERGEPERSONDIALOG_HPP

#include <QDialog>

namespace Ui {
class MergePersonDialog;
}

class MergePersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MergePersonDialog(QWidget *parent = 0);
    ~MergePersonDialog();

private:
    Ui::MergePersonDialog *ui;
};

#endif // MERGEPERSONDIALOG_HPP
