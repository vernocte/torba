#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include <QTabBar>

class MainTabWidget : public QTabWidget
{
public:
    MainTabWidget(QWidget* parent = 0);


};

class ColoredTabBar : public QTabBar
{
private:
    MainTabWidget * _parent;

public:
    ColoredTabBar(QWidget* parent = 0) : QTabBar(parent) { _parent = (MainTabWidget*)parent; }
    void  paintEvent(QPaintEvent *);
};



#endif // MAINTABWIDGET_H
