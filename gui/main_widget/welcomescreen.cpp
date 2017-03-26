#include "welcomescreen.hpp"
#include "ui_welcomescreen.h"

#include <QPainter>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    EditorBase(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::save(){ }
void WelcomeScreen::save_as(){ }
QColor WelcomeScreen::color()
{
    return QColor(60,60,60);
}
QString WelcomeScreen::type()
{
    return "Welcome";
}
int WelcomeScreen::idx()
{
    return 0;
}
bool WelcomeScreen::dirty()
{
    return false;
}

void WelcomeScreen::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
