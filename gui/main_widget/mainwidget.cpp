#include "mainwidget.hpp"
#include "ui_mainwidget.h"
#include "personwidget.hpp"
#include "eventwidget.hpp"
#include "mailfilter.hpp"
#include "../dialogs/choicedialog.hpp"

#include <QPainter>



MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(ui->main_widget,SIGNAL(tabCloseRequested(int)),this,SLOT(close_file(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::close_file(int index)
{
    if(((EditorBase*)ui->main_widget->widget(index))->dirty())
    {
        ChoiceDialog d("Spremembe niso shranjene, vseeno hočete zapreti?");
        if(d.exec())
        {
            ui->main_widget->widget(index)->deleteLater();
            ui->main_widget->removeTab(index);
        }
    }
    else
    {
        ui->main_widget->widget(index)->deleteLater();
        ui->main_widget->removeTab(index);
    }
}

void MainWidget::new_person(PersonEntity p)
{
    int idx = 0;
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "person" && ((EditorBase*)ui->main_widget->widget(i))->idx()==0)
        {
            ++idx;
        }
    }
    QString index = (idx == 0) ? "" : " " + QString::number(idx);
    PersonWidget* person = new PersonWidget(_db, p);
    connect(person, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    connect(person, SIGNAL(dirty_changed(bool)), this, SLOT(dirty(bool)));

    connect(person, SIGNAL(add_person(int,PersonBaseEntity,bool)), this, SLOT(add_person(int,PersonBaseEntity,bool)));
    connect(person, SIGNAL(remove_person(int,int,bool)), this, SLOT(remove_person(int,int,bool)));

    ui->main_widget->addTab(person, "Nova oseba " + index);
    ui->main_widget->setCurrentWidget(person);
}

void MainWidget::new_event(EventEntity e)
{
    int idx = 0;
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "event" && ((EditorBase*)ui->main_widget->widget(i))->idx()==0)
        {
            ++idx;
        }
    }
    QString index = (idx == 0) ? "" : " " + QString::number(idx);

    EventWidget* event = new EventWidget(_db, e);
    connect(event, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    connect(event, SIGNAL(open_new_person(const PersonEntity&)), this, SLOT(open_person(const PersonEntity&)));
    connect(event, SIGNAL(dirty_changed(bool)), this, SLOT(dirty(bool)));

    connect(event, SIGNAL(add_event(int,EventBaseEntity,bool)), this, SLOT(add_event(int,EventBaseEntity,bool)));
    connect(event, SIGNAL(remove_event(int,int)), this, SLOT(remove_event(int,int)));

    ui->main_widget->addTab(event, "Nov dogodek" + index);
    ui->main_widget->setCurrentWidget(event);
}

void MainWidget::new_mail_filter()
{
    int idx = 0;
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "filter" && ((EditorBase*)ui->main_widget->widget(i))->idx()==0)
        {
            ++idx;
        }
    }
    QString index = (idx == 0) ? "" : " " + QString::number(idx);
    MailFilter* mail_filter = new MailFilter();
    ui->main_widget->addTab(mail_filter, "Filter" + index);
    ui->main_widget->setCurrentWidget(mail_filter);
}

void MainWidget::change_text(QString val)
{
    ui->main_widget->setTabText(ui->main_widget->currentIndex() ,val);
}

void MainWidget::save()
{
    ((EditorBase*)ui->main_widget->currentWidget())->save();
}

void MainWidget::save_as()
{
    ((EditorBase*)ui->main_widget->currentWidget())->save_as();
}

void MainWidget::save_all()
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        ((EditorBase*)ui->main_widget->widget(i))->save();
    }
}

void MainWidget::open_person(const PersonEntity& p)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "person" && ((EditorBase*)ui->main_widget->widget(i))->idx()==p.idx())
        {
            ui->main_widget->setCurrentIndex(i);
            return;
        }
    }
    PersonWidget* person = new PersonWidget(_db, p);
    connect(person, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    connect(person, SIGNAL(dirty_changed(bool)), this, SLOT(dirty(bool)));

    connect(person, SIGNAL(add_person(int,PersonBaseEntity,bool)), this, SLOT(add_person(int,PersonBaseEntity,bool)));
    connect(person, SIGNAL(remove_person(int,int,bool)), this, SLOT(remove_person(int,int,bool)));

    ui->main_widget->addTab(person, p.name() + " " + p.surname());
    ui->main_widget->setCurrentWidget(person);
}

void MainWidget::open_event(const EventEntity& e)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "event" && ((EditorBase*)ui->main_widget->widget(i))->idx()==e.idx())
        {
            ui->main_widget->setCurrentIndex(i);
            return;
        }
    }
    EventWidget* event = new EventWidget(_db, e);
    connect(event, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    connect(event, SIGNAL(open_new_person(const PersonEntity&)), this, SLOT(open_person(const PersonEntity&)));
    connect(event, SIGNAL(dirty_changed(bool)), this, SLOT(dirty(bool)));

    connect(event, SIGNAL(add_event(int,EventBaseEntity,bool)), this, SLOT(add_event(int,EventBaseEntity,bool)));
    connect(event, SIGNAL(remove_event(int,int)), this, SLOT(remove_event(int,int)));

    ui->main_widget->addTab(event, e.name() + " " + e.type());
    ui->main_widget->setCurrentWidget(event);
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWidget::database(std::shared_ptr<Database> db)
{
    _db = db;
}

void MainWidget::dirty(bool val)
{
    QString text = ui->main_widget->tabText(ui->main_widget->currentIndex());
    if(val)
    {
        text += " *";
    }
    else
    {
        text.replace(" *", "");
    }
    ui->main_widget->setTabText(ui->main_widget->currentIndex(),text);
}

void MainWidget::add_event(int person, const EventBaseEntity& e, bool leader)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "person" && ((EditorBase*)ui->main_widget->widget(i))->idx()==person)
        {
            ((PersonWidget*)ui->main_widget->widget(i))->add_event(e, leader);
            return;
        }
    }
}

void MainWidget::remove_event(int person, int event)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "person" && ((EditorBase*)ui->main_widget->widget(i))->idx()==person)
        {
            ((PersonWidget*)ui->main_widget->widget(i))->remove_event(event);
            return;
        }
    }
}
void MainWidget::add_person(int event, const PersonBaseEntity p, bool leader)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "event" && ((EditorBase*)ui->main_widget->widget(i))->idx()==event)
        {
            ((EventWidget*)ui->main_widget->widget(i))->add_person(p, leader);
            return;
        }
    }
}
void MainWidget::remove_person(int event, int person, bool leader)
{
    for(int i=0; i<ui->main_widget->count(); ++i)
    {
        if(((EditorBase*)ui->main_widget->widget(i))->type() == "event" && ((EditorBase*)ui->main_widget->widget(i))->idx()==event)
        {
            ((EventWidget*)ui->main_widget->widget(i))->remove_person(person, leader);
            return;
        }
    }
}
