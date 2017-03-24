#ifndef FILTERTABLEWIDGET_HPP
#define FILTERTABLEWIDGET_HPP

#include <QTableWidget>
#include <QKeyEvent>

class FilterTableWidget : public QTableWidget
{
public:
    FilterTableWidget(QWidget *parent);
    FilterTableWidget(int rows, int columns, QWidget *parent);
    void keyPressEvent(QKeyEvent* event);
};

#endif // FILTERTABLEWIDGET_HPP
