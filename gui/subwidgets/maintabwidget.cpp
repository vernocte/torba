#include "maintabwidget.hpp"
#include <QStylePainter>
#include "../main_widget/editorbase.hpp"

MainTabWidget::MainTabWidget(QWidget *parent) : QTabWidget(parent)
{
    setTabBar(new ColoredTabBar(this));
}

void  ColoredTabBar::paintEvent(QPaintEvent*)
{
        QPainter painter(this);
        painter.save();
        for(int i=0; i<count(); ++i)
        {
            QRect Rect = tabRect(i);
            QColor color = ((EditorBase*)(_parent->widget(i)))->color();
            if(i != currentIndex()) color = color.darker(130);

            Rect.adjust(0,0,0,1);

            QBrush brush = QBrush(color);
            painter.fillRect(Rect, brush);
            Rect.adjust(5,0,0,0);
            painter.setPen(QPen(QColor(Qt::white)));
            painter.drawText(Rect, Qt::AlignVCenter | Qt::AlignLeft,
                             tabText(i));
        }
        painter.restore();
}
