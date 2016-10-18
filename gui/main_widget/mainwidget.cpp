#include "mainwidget.hpp"
#include "ui_mainwidget.h"
#include "personwidget.hpp"
#include "eventwidget.hpp"
#include "mailfilter.hpp"
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
    ui->main_widget->widget(index)->deleteLater();
    ui->main_widget->removeTab(index);
}

void MainWidget::new_person(PersonEntity p)
{
    PersonWidget* person = new PersonWidget(_db, p);
    connect(person, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    ui->main_widget->addTab(person, "Nova oseba");
    ui->main_widget->setCurrentWidget(person);
}

void MainWidget::new_event(EventEntity e)
{
    EventWidget* event = new EventWidget(_db, e);
    connect(event, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    ui->main_widget->addTab(event, "Nov dogodek");
    ui->main_widget->setCurrentWidget(event);
}

void MainWidget::new_mail_filter()
{
    MailFilter* mail_filter = new MailFilter();
    ui->main_widget->addTab(mail_filter, "Mail filter");
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
    PersonWidget* person = new PersonWidget(_db, p);
    connect(person, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
    ui->main_widget->addTab(person, p.name() + " " + p.surname());
    ui->main_widget->setCurrentWidget(person);
}

void MainWidget::open_event(const EventEntity& e)
{
    EventWidget* event = new EventWidget(_db, e);
    connect(event, SIGNAL(base_text(QString)), this, SLOT(change_text(QString)));
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
