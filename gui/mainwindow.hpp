#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include<memory>

#include <QMainWindow>

#include "backend/config.hpp"
#include "backend/database.hpp"
#include "backend/logger.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void open_person(PersonEntity);
    void open_event(EventEntity);
    void new_person();
    void new_event();
    void new_filter();

private slots:
    void save_settings();
    void restore();
    void new_database();
    void open_database();
    void open_database(const QString& path);
    void save();
    void save_as();
    void save_all();
    void emit_new_person();
    void emit_new_event();
    void emit_new_filter();
    void emit_open_person();
    void emit_open_event();
    void delete_person();
    void delete_event();
    void export_database();

private:

    Ui::MainWindow *ui;
    Config _config;
    bool _connected;

    std::shared_ptr<Logger> _logger;
    std::shared_ptr<Database> _db;
};

#endif // MAINWINDOW_HPP
