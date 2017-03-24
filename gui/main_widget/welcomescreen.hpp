#ifndef WELCOMESCREEN_HPP
#define WELCOMESCREEN_HPP

#include <QWidget>
#include "editorbase.hpp"

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public EditorBase
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();

    virtual void save() override;
    virtual void save_as() override;
    virtual QColor color() override;
    virtual QString type() override;
    virtual int idx() override;
    virtual bool dirty() override;

private:
    Ui::WelcomeScreen *ui;
};

#endif // WELCOMESCREEN_HPP
