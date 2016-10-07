#ifndef SETTINGSWIDGETBASE_HPP
#define SETTINGSWIDGETBASE_HPP

#include <QWidget>

namespace Ui {
class SettingsWidgetBase;
}

class SettingsWidgetBase : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidgetBase(QWidget *parent = 0);
    ~SettingsWidgetBase();

public slots:
    void visible(bool val);
    void favourite(bool val);
    bool favourite();

signals:
    void favourite_changed(bool);

private slots:
    void on_fav_button_toggled(bool checked);

protected:
    Ui::SettingsWidgetBase *ui;
};

#endif // SETTINGSWIDGETBASE_HPP
