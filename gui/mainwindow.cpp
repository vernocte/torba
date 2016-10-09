#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QShortcut>

#include "dialogs/openpersondialog.hpp"
#include "dialogs/openeventdialog.hpp"
#include "dialogs/messagedialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _config(),
    _connected(false),
    _logger(new Logger()),
    _db()
{
    ui->setupUi(this);

    QSqlDatabase::addDatabase("QSQLITE");

    connect(ui->settings, SIGNAL(new_person()), ui->main_widget, SLOT(new_person()));
    connect(ui->settings, SIGNAL(new_event()), ui->main_widget, SLOT(new_event()));
    connect(ui->settings, SIGNAL(new_mail_filter()), ui->main_widget, SLOT(new_mail_filter()));
    connect(ui->settings, SIGNAL(new_database(QString)), this, SLOT(new_or_open_db(QString)));
    connect(ui->settings, SIGNAL(open_database(QString)), this, SLOT(new_or_open_db(QString)));
    connect(ui->settings, SIGNAL(open_person()), this, SLOT(emit_open_person()));
    connect(ui->settings, SIGNAL(open_event()), this, SLOT(emit_open_event()));
    connect(this, SIGNAL(open_person(PersonEntity)), ui->main_widget, SLOT(open_person(PersonEntity)));
    connect(this, SIGNAL(open_event(EventEntity)), ui->main_widget, SLOT(open_event(EventEntity)));
    connect(ui->settings, SIGNAL(delete_person()), this, SLOT(delete_person()));
    connect(ui->settings, SIGNAL(delete_event()), this, SLOT(delete_event()));
    connect(ui->settings, SIGNAL(save_file()), this, SLOT(save()));
    connect(ui->settings, SIGNAL(save_file_as()), this, SLOT(save_as()));
    connect(ui->settings, SIGNAL(save_all()), this, SLOT(save_all()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(save()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S), this, SLOT(save_as()));

    ui->bottom_bar->display("Ni povezave na bazo!", true);

    restore();
}

MainWindow::~MainWindow()
{
    save_settings();
    delete ui;
}

void MainWindow::restore()
{
    resize(_config.size());
    move(_config.position());
    if(_config.fullscreen()) showFullScreen();

    ui->settings->set_favourites(_config);
}

void MainWindow::save_settings()
{
    _config.size(size());
    _config.position(pos());
    _config.fullscreen(isFullScreen());

    ui->settings->save_favourites(_config);
}

void MainWindow::new_or_open_db(QString path)
{
    try
    {
        _connected &= false;
        _db.reset(new Database(path, _logger));
        _connected |= true;
        ui->bottom_bar->display("Povezan z bazo " + QFileInfo(path).fileName() +"!", false);
    }
    catch(const std::exception&)
    {
        ui->bottom_bar->display("Napaka pri povezavi na bazo " + QFileInfo(path).fileName() +"!", true);
        _connected &= false;
    }
}

void MainWindow::save()
{
    if(_connected)
    {
        ui->main_widget->save(_db);
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::save_as()
{
    if(_connected)
    {
        ui->main_widget->save_as(_db);
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::save_all()
{
    if(_connected)
    {
        ui->main_widget->save_all(_db);
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::emit_open_person()
{
    if(_connected)
    {
        OpenPersonDialog* person_dialog = new OpenPersonDialog(_db);
        if(person_dialog->exec())
        {
            std::vector<PersonEntity> p = person_dialog->person();
            for(auto it = p.begin(); it!=p.end(); ++it)
            {
                emit open_person(*it);
            }
        }
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::emit_open_event()
{
    if(_connected)
    {
        OpenEventDialog* event_dialog = new OpenEventDialog(_db);
        if(event_dialog->exec())
        {
            std::vector<EventEntity> e = event_dialog->event();
            for(auto it = e.begin(); it!=e.end(); ++it)
            {
                emit open_event(*it);
            }
        }
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::delete_person()
{
    if(_connected)
    {
        OpenPersonDialog* person_dialog = new OpenPersonDialog(_db);
        if(person_dialog->exec())
        {
            std::vector<int> selected = person_dialog->index();
            for(auto it=selected.begin(); it!=selected.end(); ++it)
            {
                _db->delete_person(*it);
            }
        }
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}

void MainWindow::delete_event()
{
    if(_connected)
    {
        OpenEventDialog* event_dialog = new OpenEventDialog(_db);
        if(event_dialog->exec())
        {
            std::vector<int> selected = event_dialog->index();
            for(auto it=selected.begin(); it!=selected.end(); ++it)
            {
                _db->delete_event(*it);
            }
        }
    }
    else
    {
        MessageDialog message("Niste povezani na bazo!");
        message.exec();
    }
}
