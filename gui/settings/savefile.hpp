#ifndef SAVEFILE_HPP
#define SAVEFILE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "settingswidgetbase.hpp"

namespace Ui {
class SaveFile;
}

class SaveFile : public SettingsWidgetBase
{
    Q_OBJECT

public:
    explicit SaveFile(QWidget *parent = 0);
    ~SaveFile();

public slots:

signals:
    void save_file();
    void save_file_as();
    void save_all();

private slots:
    void on_save_button_clicked();
    void on_save_as_button_clicked();
    void on_save_all_button_clicked();

private:

    QPushButton* save_button;
    QPushButton* save_as_button;
    QPushButton* save_all_button;
};

#endif // SAVEFILE_HPP
