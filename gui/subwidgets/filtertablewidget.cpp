#include "filtertablewidget.hpp"

#include <QApplication>
#include <QClipboard>

FilterTableWidget::FilterTableWidget(int rows, int columns, QWidget *parent = Q_NULLPTR) : QTableWidget(rows, columns, parent) {}

FilterTableWidget::FilterTableWidget(QWidget *parent = Q_NULLPTR) : QTableWidget(parent) { }

void FilterTableWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->matches(QKeySequence::Copy))
    {
        QModelIndexList cells = selectedIndexes();
        qSort(cells); // Necessary, otherwise they are in column order

        QString text;
        int currentRow = 0; // To determine when to insert newlines
        foreach (const QModelIndex& cell, cells) {
            if (text.length() == 0) {
                // First item
            } else if (cell.row() != currentRow) {
                // New row
                text += '\n';
            } else {
                // Next cell
                text += ';';
            }
            currentRow = cell.row();
            text += cell.data().toString();
        }

        QApplication::clipboard()->setText(text);
    }
}
