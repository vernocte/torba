#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP

#include <QWidget>

namespace Ui {
class BottomBar;
}

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = 0);
    ~BottomBar();
    void display(QString msg, bool err);
private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_HPP
