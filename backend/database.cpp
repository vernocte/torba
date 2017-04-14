#include "database.hpp"

#include "exceptions/databaseexception.hpp"

#include <QDebug>
#include <sstream>
#include <algorithm>

// ### Private functions

// #### Create database
void Database::create_database()
{
    _db.open();

    _logger->log("Started database creation");

    QSqlQuery query;

    // ##### Create tables

    // person
    if(!query.exec("create table person (idx integer primary key, name text not null, surname text not null);"))
    {
        throw DatabaseException("create", "person", query.lastError().text().toStdString());
    }

    // person_property
    if(!query.exec("create table person_property (idx integer primary key, property text not null);"))
    {
        throw DatabaseException("create", "person_property", query.lastError().text().toStdString());
    }
    if(!query.exec("insert into person_property values"
               "(1,  'birthday'),"
               "(2,  'birthplace'),"
               "(3,  'email'),"
               "(4,  'street'),"
               "(5,  'street_number'),"
               "(6,  'post'),"
               "(7,  'postal_number'),"
               "(8,  'country'),"
               "(9,  'phone'),"
               "(10, 'sex'),"
               "(11, 'comment'),"
               "(12, 'role'),"
               "(13, 'family');"))
    {
        throw DatabaseException("insert", "person_property", query.lastError().text().toStdString());
    }

    // person_data
    if(!query.exec("create table person_data (idx integer primary key, idx_person integer not null, "
               "idx_property integer not null, value text);"))
    {
        throw DatabaseException("create", "person_property", query.lastError().text().toStdString());
    }

    // event
    if(!query.exec("create table event (idx integer primary key, name text not null, type text not null);"))
    {
        throw DatabaseException("create", "event", query.lastError().text().toStdString());
    }

    // event_property
    if(!query.exec("create table event_property (idx integer primary key, property text not null);"))
    {
        throw DatabaseException("create", "event_property", query.lastError().text().toStdString());
    }
    if(!query.exec("insert into event_property values"
               "(1, 'start_date'),"
               "(2, 'end_date'),"
               "(3, 'comment');"))
    {
        throw DatabaseException("insert", "event_property", query.lastError().text().toStdString());
    }

    // event_data
    if(!query.exec("create table event_data (idx integer primary key, idx_event integer not null,"
               "idx_property integer not null, value text);"))
    {
        throw DatabaseException("create", "event_data", query.lastError().text().toStdString());
    }

    // attendance
    if(!query.exec("create table attendance (idx integer primary key, idx_person integer not null,"
               "idx_event integer not null, leader int not null);"))
    {
        throw DatabaseException("create", "attendance", query.lastError().text().toStdString());
    }

    // role
    if(!query.exec("create table role (idx integer primary key, value text not null);"))
    {
        throw DatabaseException("create", "role", query.lastError().text().toStdString());
    }

    // family
    if(!query.exec("create table family (idx integer primary key, value text not null);"))
    {
        throw DatabaseException("create", "family", query.lastError().text().toStdString());
    }

    // system_info
    if(!query.exec("create table system_info (idx integer primary key, property text not null, value text not null);"))
    {
        throw DatabaseException("create", "system_info", query.lastError().text().toStdString());
    }
    if(!query.exec("insert into system_info values"
               "(1, 'program version', '0.1.0-beta'),"
               "(2, 'database version', '0.1.0-beta');"))
    {
        throw DatabaseException("insert", "system_info", query.lastError().text().toStdString());
    }

    _db.close();
    _logger->log("Database successfully created");
}

// ### Constructors

// #### File and logger constructor
Database::Database(QString path, std::shared_ptr<Logger> &logger) :
    _db(QSqlDatabase::database()), _logger(logger), _path(path)
{
    bool create = !QFileInfo(path).exists();
    _db.setDatabaseName(path);
    if(create)
    {
        create_database();
        _logger->log("Database " + path + " successfuly created");
    }
    _logger->log("Database " + path + " successfuly opened");
}

// ### Destructor
Database::~Database()
{
    // because, reasons
    _db = QSqlDatabase();

    _logger->log("Database closed");
}

/*
#### Folder

[returns]: folder database is in
*/
QString Database::folder() const
{
    return QFileInfo(_path).absoluteDir().absolutePath();
}

/*
#### Folder

[returns]: folder database is in
*/
QString Database::path() const
{
    return _path;
}

/*
#### insert person

[p]: person to insert
[returns]: index of inserted person
*/
int Database::insert_person(const PersonEntity &p)
{
    _db.open();
    QSqlQuery query;

    int idx = p.idx();
    if(p.idx() == 0)
    {
        // insert person
        query.prepare("insert into  person(name, surname) values(:name, :surname);");
        query.bindValue(":name", p.name());
        query.bindValue(":surname", p.surname());
        if(!query.exec())
        {
            throw DatabaseException("insert", "person", query.lastError().text().toStdString());
        }

        // get index
        if(!query.exec("SELECT last_insert_rowid();"))
        {
            throw DatabaseException("select", "idx", query.lastError().text().toStdString());
        }
        if (query.next())
        {
            idx = query.value(0).toInt();
        }
    }
    else
    {
        // insert person
        query.prepare("insert into  person(idx, name, surname) values(:idx, :name, :surname);");
        query.bindValue(":name", p.name());
        query.bindValue(":surname", p.surname());
        query.bindValue(":idx", p.idx());
        if(!query.exec())
        {
            throw DatabaseException("insert", "person", query.lastError().text().toStdString());
        }
    }

    // insert person data
    query.prepare("INSERT INTO person_data (idx_person, idx_property, value) values"
                  "(:idx, 1, :birthday),"
                  "(:idx, 2, :birthplace),"
                  "(:idx, 3, :email),"
                  "(:idx, 4, :street),"
                  "(:idx, 5, :street_number),"
                  "(:idx, 6, :post),"
                  "(:idx, 7, :postal_number),"
                  "(:idx, 8, :country),"
                  "(:idx, 9, :phone),"
                  "(:idx, 10, :sex),"
                  "(:idx, 11, :comment);");
    query.bindValue(":idx", idx);
    query.bindValue(":birthday", p.birthday().toString("yyyy-MM-dd"));
    query.bindValue(":birthplace", p.birthplace());
    query.bindValue(":email", p.email());
    query.bindValue(":street",p.street());
    query.bindValue(":street_number", p.street_number());
    query.bindValue(":post", p.post());
    query.bindValue(":postal_number", p.postal_number());
    query.bindValue(":country", p.country());
    query.bindValue(":phone", p.phone());
    query.bindValue(":sex", (p.sex()) ? "female" : "male");
    query.bindValue(":comment", p.comment());

    if(!query.exec())
    {
        throw DatabaseException("insert", "person_data", query.lastError().text().toStdString());
    }

    // roles
    for(auto it = p.roles().begin(); it!=p.roles().end(); ++it)
    {
        query.prepare("insert into person_data (idx_person, idx_property, value) values (:idx, 12, (select idx from role where value = :value))");
        query.bindValue(":idx", idx);
        query.bindValue(":value", *it);
        if(!query.exec())
        {
            throw DatabaseException("insert", "person_data", query.lastError().text().toStdString());
        }
    }

    // attendance
    for(auto it=p.lead().begin(); it!=p.lead().end(); ++it)
    {
        query.prepare("insert into attendance(idx_person, idx_event, leader) values (:idx, :idx_event, 1)");
        query.bindValue(":idx", idx);
        query.bindValue(":idx_event", it->idx());
        if(!query.exec())
        {
            throw DatabaseException("insert", "attendance", query.lastError().text().toStdString());
        }
    }
    for(auto it=p.participated().begin(); it!=p.participated().end(); ++it)
    {
        query.prepare("insert into attendance(idx_person, idx_event, leader) values (:idx, :idx_event, 0)");
        query.bindValue(":idx", idx);
        query.bindValue(":idx_event", it->idx());
        if(!query.exec())
        {
            throw DatabaseException("insert", "attendance", query.lastError().text().toStdString());
        }
    }

    _db.close();
    return idx;
}

/*
#### delete person

[p]: person to insert
[returns]: index of inserted person
*/
void Database::delete_person(int idx)
{
    _db.open();
    QSqlQuery query;

    // person data
    query.prepare("delete from person_data where idx_person = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("delete", "person_data", query.lastError().text().toStdString());
    }

    // attendace
    query.prepare("delete from attendance where idx_person = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("delete", "attendance", query.lastError().text().toStdString());
    }

    // person
    query.prepare("delete from person where idx = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("delete", "person", query.lastError().text().toStdString());
    }

    _db.close();
}

/*
#### save person

[p]: person to save
*/
void Database::save_person(const PersonEntity& p)
{
    delete_person(p.idx());
    insert_person(p);
}

/*
#### get person

[idx]: index of person
[returns]: person with given index
*/
PersonEntity Database::get_person(int idx)
{
    // return new person
    if(idx==0) return PersonEntity();

    _db.open();
    QSqlQuery query;

    // resulting entity
    PersonEntity p;

    // set idx
    p.idx(idx);

    // read person
    query.prepare("select name, surname from person where idx = :idx;");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("select", "person", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        p.name(query.value(0).toString());
        p.surname(query.value(1).toString());
    }

    // person_data

    std::vector<int> role_idx;

    query.prepare("select idx_property, value from person_data where idx_person = :idx;");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("select", "person_data", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        switch (query.value(0).toInt())
        {
        case 1:
            p.birthday(query.value(1).toDate());
            break;
        case 2:
            p.birthplace(query.value(1).toString());
            break;
        case 3:
            p.email(query.value(1).toString());
            break;
        case 4:
            p.street(query.value(1).toString());
            break;
        case 5:
            p.street_number(query.value(1).toString());
            break;
        case 6:
            p.post(query.value(1).toString());
            break;
        case 7:
            p.postal_number(query.value(1).toString().toInt());
            break;
        case 8:
            p.country(query.value(1).toString());
            break;
        case 9:
            p.phone(query.value(1).toString());
            break;
        case 10:
            p.sex(query.value(1).toString() == "female");
            break;
        case 11:
            p.comment(query.value(1).toString());
            break;
        case 12:
            role_idx.emplace_back(query.value(1).toInt());
            break;
        default:
            throw DatabaseException("select", "person_data", "Unrecognised index: " + query.value(0).toString().toStdString());
        }
    }

    // roles
    for(auto it=role_idx.begin(); it!=role_idx.end(); ++it)
    {
        query.prepare("select value from role where idx = :idx;");
        query.bindValue(":idx", *it);
        if(!query.exec())
        {
            throw DatabaseException("select", "role", query.lastError().text().toStdString());
        }
        while (query.next())
        {
            p.roles().emplace_back(query.value(0).toString());
        }
    }

    // attendance
    query.prepare("select idx, name, type from event where idx in (select idx_event from attendance where idx_person = :idx_person and leader = 0);");
    query.bindValue(":idx_person", p.idx());
    if(!query.exec())
    {
        throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        p.participated().emplace_back(EventBaseEntity(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()));
    }

    // attendance leading
    query.prepare("select idx, name, type from event where idx in (select idx_event from attendance where idx_person = :idx_person and leader = 1);");
    query.bindValue(":idx_person", p.idx());
    if(!query.exec())
    {
        throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        p.lead().emplace_back(EventBaseEntity(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()));
    }

    _db.close();
    return p;
}

/*
#### get list of persons

[idx]: index of person
[returns]: person with given index
*/
std::vector<PersonBaseEntity> Database::person_list()
{
    _db.open();
    QSqlQuery query;

    std::vector<PersonBaseEntity> values;

    // read persons
    if(!query.exec("select idx, name, surname from person;"))
    {
        throw DatabaseException("select", "person", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        values.emplace_back(PersonBaseEntity(query.value(0).toInt(), query.value(1).toString(),  query.value(2).toString()));
    }

    _db.close();

    return values;
}


void Database::save_event(EventEntity e)
{
    delete_event(e.idx());
    insert_event(e);
}

EventEntity Database::get_event(int idx)
{
    _db.open();
    EventEntity e;
    QSqlQuery query;
    query.prepare("select name, type from event where idx= :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("select", "event", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        e.name(query.value(0).toString());
        e.type(query.value(1).toString());
        e.idx(idx);
    }

    query.prepare("select idx_property, value from event_data where idx_event = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("select", "event_data", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        switch(query.value(0).toInt())
        {
        case 1:
            e.start_date(query.value(1).toDate());
        case 2:
            e.end_date(query.value(1).toDate());
        case 3:
            e.comment(query.value(1).toString());
        default:
            break;
        }
    }

    // attendance
    query.prepare("select idx, name, surname from person where idx in (select idx_person from attendance where idx_event = :idx_event and leader = 0);");
    query.bindValue(":idx_event", e.idx());
    if(!query.exec())
    {
        throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        e.participants().emplace_back(PersonBaseEntity(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()));
    }

    // attendance leading
    query.prepare("select idx, name, surname from person where idx in (select idx_person from attendance where idx_event = :idx_event and leader = 1);");
    query.bindValue(":idx_event", e.idx());
    if(!query.exec())
    {
        throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
    }
    while (query.next())
    {
        e.leaders().emplace_back(PersonBaseEntity(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()));
    }

    _db.close();
    return e;
}

int Database::insert_event(EventEntity e)
{
    _db.open();
    QSqlQuery query;

    if(e.idx()==0)
    {
        query.prepare("insert into  event(name, type) VALUES(:name, :type);");
        query.bindValue(":name", e.name());
        query.bindValue(":type", e.type());
        if(!query.exec())
        {
            throw DatabaseException("insert", "event", query.lastError().text().toStdString());
        }
        if(!query.exec("select last_insert_rowid();"))
        {
            throw DatabaseException("select", "last_insert_rowid", query.lastError().text().toStdString());
        }
        int idx = 0;

        while (query.next())
        {
            idx = query.value(0).toInt();
        }
        if(idx!=0) e.idx(idx);
        else throw DatabaseException("select", "index", "");
    }
    else
    {
        query.prepare("insert into  event(idx, name, type) VALUES(:idx, :name, :type);");
        query.bindValue(":idx", e.idx());
        query.bindValue(":name", e.name());
        query.bindValue(":type", e.type());
        if(!query.exec())
        {
            throw DatabaseException("insert", "event", query.lastError().text().toStdString());
        }
    }

    query.prepare("insert into event_data (idx_event, idx_property, value) VALUES"
                  "(:idx, 1, :start_date),"
                  "(:idx, 2, :end_date),"
                  "(:idx, 3, :comment);");
    query.bindValue(":idx", e.idx());
    query.bindValue(":start_date", e.start_date().toString("yyyy-MM-dd"));
    query.bindValue(":end_date", e.end_date().toString("yyyy-MM-dd"));
    query.bindValue(":comment", e.comment());
    if(!query.exec())
    {
        throw DatabaseException("insert", "event_data", query.lastError().text().toStdString());
    }

    // attendance
    for(auto it=e.leaders().begin(); it!=e.leaders().end(); ++it)
    {
        query.prepare("insert into attendance(idx_person, idx_event, leader) values (:idx_person, :idx, 1)");
        query.bindValue(":idx_person", it->idx());
        query.bindValue(":idx", e.idx());
        if(!query.exec())
        {
            throw DatabaseException("insert", "attendance", query.lastError().text().toStdString());
        }
    }
    for(auto it=e.participants().begin(); it!=e.participants().end(); ++it)
    {
        query.prepare("insert into attendance(idx_person, idx_event, leader) values (:idx_person, :idx, 0)");
        query.bindValue(":idx_person", it->idx());
        query.bindValue(":idx", e.idx());
        if(!query.exec())
        {
            throw DatabaseException("insert", "attendance", query.lastError().text().toStdString());
        }
    }

    _db.close();

    return e.idx();
}

std::vector<EventBaseEntity> Database::event_list()
{
    _db.open();
    QSqlQuery query;
    std::vector<EventBaseEntity> events;
    if(!query.exec("select idx, name, type from event;"))
    {
        throw DatabaseException("select", "event", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        EventBaseEntity e;
        e.idx(query.value(0).toInt());
        e.name(query.value(1).toString());
        e.type(query.value(2).toString());
        events.emplace_back(e);
    }
    _db.close();
    return events;
}

void Database::delete_event(int idx)
{
    _db.open();
    QSqlQuery query;
    query.prepare("delete from event where idx = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("delete", "event", query.lastError().text().toStdString());
    }
    query.prepare("DELETE from event_data where idx_event = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
    }
    _db.close();
}

// ### category

/*
#### categories list

[returns]: vector containing all categories
*/
QStringList Database::categories_list()
{
    _db.open();
    QSqlQuery query;

    QStringList roles;
    if(!query.exec("select value from role;"))
    {
        throw DatabaseException("select", "role", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        roles.append(query.value(0).toString());
    }
    _db.close();
    return roles;
}

/*
#### add category

[category]: category to add
*/
void Database::add_category(const QString& category)
{
    _db.open();
    QSqlQuery query;
    query.prepare("insert into role (value) values (:category)");
    query.bindValue(":category", category);
    if(!query.exec())
    {
        throw DatabaseException("insert", "role", query.lastError().text().toStdString());
    }
    _db.close();
}

QString vec_to_string(const std::vector<int>& vec)
{
    std::stringstream ss;
    ss << "(";
    std::string delim = "";
    for(int i: vec)
    {
        ss<< delim << i;
        delim = ", ";
    }
    ss << ")";
    return QString::fromStdString(ss.str());
}

QStringList Database::event_type_list()
{
    _db.open();
    QSqlQuery query;
    QStringList types;
    if(!query.exec("select distinct type from event;"))
    {
        throw DatabaseException("select", "event type", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        types.append(query.value(0).toString());
    }
    _db.close();
    return types;
}

void Database::export_database(const std::vector<int>& index, const QString& path)
{
    _db.open();
    QSqlQuery query;
    query.prepare("attach :path as db");
    query.bindValue(":path", path);
    if(!query.exec())
    {
        throw DatabaseException("attach", "db", query.lastError().text().toStdString());
    }
    QString idx = vec_to_string(index);

    query.prepare("insert into db.role(idx, value)"
                  "select idx, value from role;");
    if(!query.exec())
    {
        throw DatabaseException("insert", "event", query.lastError().text().toStdString());
    }
    query.prepare("insert into db.event(idx, name, type) select idx, name, type from event where idx in " + idx + ";");
    if(!query.exec())
    {
        throw DatabaseException("insert", "event", query.lastError().text().toStdString());
    }
    query.prepare("insert into db.event_data(idx, idx_event, idx_property, value) "
                  "select idx, idx_event, idx_property, value from event_data where idx_event in " + idx + ";");
    if(!query.exec())
    {
        throw DatabaseException("insert", "event", query.lastError().text().toStdString());
    }
    query.prepare("insert into db.person(idx, name, surname) "
                  "select idx, name, surname from person where idx in "
                  "(select idx_person from attendance where idx_event in " + idx +");");
    if(!query.exec())
    {
        throw DatabaseException("insert", "event", query.lastError().text().toStdString());
    }

    query.prepare("insert into db.person_data(idx, idx_person, idx_property, value) "
                  "select idx, idx_person, idx_property, value from person_data where idx_person in "
                  "(select idx_person from attendance where idx_event in " + idx +");");
    if(!query.exec())
    {
        throw DatabaseException("insert", "event", query.lastError().text().toStdString());
    }

    query.prepare("insert into db.attendance(idx, idx_person, idx_event, leader) "
                  "select idx, idx_person, idx_event, leader from attendance where idx_event in " + idx + ";");
    if(!query.exec())
    {
        throw DatabaseException("insert", "attendace", query.lastError().text().toStdString());
    }

    _db.close();
}

std::vector<EventBaseEntity> Database::events_between(const QDate& start, const QDate& end, const QString& event_type)
{
    _db.open();
    QSqlQuery query;
    std::vector<EventBaseEntity> events;
    if(event_type!="")
    {
        query.prepare("select idx, name, type from event  where type = :type and idx in (select idx_event from event_data where idx_property = 1 and value > :start) "
                      "and idx in (select idx_event from event_data where idx_property = 2 and value < :end)");
        query.bindValue(":type", event_type);
    }
    else
    {
        query.prepare("select idx, name, type from event  where idx in (select idx_event from event_data where idx_property = 1 and value > :start) "
                      "and idx in (select idx_event from event_data where idx_property = 2 and value < :end)");
    }

    query.bindValue(":start", start.toString("yyyy-MM-dd"));
    query.bindValue(":end", end.toString("yyyy-MM-dd"));
    if(!query.exec())
    {
        throw DatabaseException("select", "events between", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        events.emplace_back(EventBaseEntity(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString()));
    }
    _db.close();
    return events;
}

std::vector<PersonEntity> Database::filter(const FilterEntity& filter)
{
    _db.open();
    QSqlQuery query;

    std::vector<int> person_idx;

    // get all idxes
    query.prepare("select idx from person");
    if(!query.exec())
    {
        throw DatabaseException("select", "person", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        person_idx.emplace_back(query.value(0).toInt());
    }


    // if event's used, filter out
    if(filter.use_events())
    {
        if(filter.events().empty())
        {
            return std::vector<PersonEntity>();
        }
        else
        {
            query.prepare("select idx_person from attendance where idx_event in " + vec_to_string(filter.events()));
            if(!query.exec())
            {
                throw DatabaseException("select", "person_data", query.lastError().text().toStdString());
            }
            while(query.next())
            {
                person_idx.emplace_back(query.value(0).toInt());
            }
        }
    }

    // if category selected, filter out
    if(filter.use_category())
    {
        int role_idx = -1;
        // get idx of category
        query.prepare("select idx from role where value = :role");
        query.bindValue(":role", filter.person_category());
        if(!query.exec())
        {
            throw DatabaseException("select", "attendance", query.lastError().text().toStdString());
        }
        while(query.next())
        {
            role_idx = query.value(0).toInt();
        }

        query.prepare("select idx_person from person_data where idx_property = 12 and value = :role_idx and idx_person in " + vec_to_string(person_idx));
        query.bindValue(":role_idx", role_idx);
        if(!query.exec())
        {
            throw DatabaseException("select", "person_data", query.lastError().text().toStdString());
        }
        person_idx.clear();
        while(query.next())
        {
            person_idx.emplace_back(query.value(0).toInt());
        }
    }

    if(filter.use_birth())
    {
        query.prepare("select idx_person from person_data where idx_property = 1 and value > :birth_start and value < :birth_end and idx_person in " + vec_to_string(person_idx));
        query.bindValue(":birth_start", filter.born_from().toString("yyyy-mm-dd"));
        query.bindValue(":birth_end", filter.born_to().toString("yyyy-mm-dd"));
        if(!query.exec())
        {
            throw DatabaseException("select", "person_data", query.lastError().text().toStdString());
        }
        person_idx.clear();
        while(query.next())
        {
            person_idx.emplace_back(query.value(0).toInt());
        }
    }

    person_idx.erase(unique_elements(person_idx.begin(), person_idx.end()), person_idx.end());

    std::vector<PersonEntity> people;
    for(int i : person_idx)
    {
        people.emplace_back(get_person(i));
    }
    return people;
}


std::vector<int>::iterator Database::unique_elements(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    while (first != last)
    {
        std::vector<int>::iterator next(first);
        last = std::remove(++next, last, *first);
        first = next;
    }

    return last;
}

std::map<int, int> Database::merge_roles(const QString &path)
{
    _db.open();
    QSqlQuery query;
    query.prepare("attach :path as db");
    query.bindValue(":path", path);
    if(!query.exec())
    {
        throw DatabaseException("attach", "db", query.lastError().text().toStdString());
    }
    query.prepare("select idx, value from db.role");
    if(!query.exec())
    {
        throw DatabaseException("select", "db.role", query.lastError().text().toStdString());
    }
    std::map<int, int> roles;
    while(query.next())
    {
        QString value = query.value(1).toString();
        QSqlQuery query2;
        query2.prepare("select idx from role where value = :value");
        query2.bindValue(":value", value);
        if(!query2.exec())
        {
            throw DatabaseException("select", "role", query.lastError().text().toStdString());
        }
        if(query2.next())
        {
            roles[query.value(0).toInt()] = query2.value(0).toInt();
        }
        else
        {
            // insert role
            query2.prepare("insert into  role(value) values(:value);");
            query2.bindValue(":value", value);
            if(!query2.exec())
            {
                throw DatabaseException("insert", "role", query.lastError().text().toStdString());
            }
            // get index
            if(!query2.exec("SELECT last_insert_rowid();"))
            {
                throw DatabaseException("select", "index",query.lastError().text().toStdString());
            }
            if(query2.next())
            {
                roles[query.value(0).toInt()] = query2.value(0).toInt();
            }
        }
    }
    _db.close();
    return roles;
}

std::vector<EventEntity> Database::get_events(const QString& path)
{
    _db.open();
    QSqlQuery query;
    query.prepare("attach :path as db");
    query.bindValue(":path", path);
    if(!query.exec())
    {
        throw DatabaseException("attach", "db", query.lastError().text().toStdString());
    }
    std::vector<EventEntity> events;
    if(!query.exec("select idx, name, type from db.event;"))
    {
        throw DatabaseException("select", "db.event", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        EventEntity e;
        e.idx(query.value(0).toInt());
        e.name(query.value(1).toString());
        e.type(query.value(2).toString());
        events.emplace_back(e);
    }
    for(EventEntity& e : events)
    {
        query.prepare("select idx_property, value from db.event_data where idx_event = :idx");
        query.bindValue(":idx", e.idx());
        if(!query.exec())
        {
            throw DatabaseException("select", "db.event_data", query.lastError().text().toStdString());
        }
        while(query.next())
        {
            switch(query.value(0).toInt())
            {
            case 1:
                e.start_date(query.value(1).toDate());
            case 2:
                e.end_date(query.value(1).toDate());
            case 3:
                e.comment(query.value(1).toString());
            default:
                break;
            }
        }
    }

    _db.close();
    return events;
}

int Database::event_exists(const QString& name, const QString& type)
{
    int idx = -1;
    _db.open();
    QSqlQuery query;
    query.prepare("select idx from event where name = :name and type = :type");
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    if(!query.exec())
    {
        throw DatabaseException("select idx", "event", query.lastError().text().toStdString());
    }
    if(query.next())
    {
        idx = query.value(0).toInt();
    }
    _db.close();
    return idx;
}

int Database::person_exists(const QString& name, const QString& surname)
{
    int idx = -1;
    _db.open();
    QSqlQuery query;
    query.prepare("select idx from person where name = :name and surname = :surname");
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    if(!query.exec())
    {
        throw DatabaseException("select idx", "person", query.lastError().text().toStdString());
    }
    if(query.next())
    {
        idx = query.value(0).toInt();
    }
    _db.close();
    return idx;
}

std::vector<EventEntity> Database::get_persons(const QString& path)
{
    _db.open();
    QSqlQuery query;
    query.prepare("attach :path as db");
    query.bindValue(":path", path);
    if(!query.exec())
    {
        throw DatabaseException("attach", "db", query.lastError().text().toStdString());
    }
    std::vector<PersonEntity> persons;
    if(!query.exec("select idx, name, surname from db.person;"))
    {
        throw DatabaseException("select", "db.event", query.lastError().text().toStdString());
    }
    while(query.next())
    {
        PersonEntity p;
        p.idx(query.value(0).toInt());
        p.name(query.value(1).toString());
        p.surname(query.value(2).toString());
        persons.emplace_back(e);
    }
    for(PersonEntity& p : persons)
    {
        // person_data

        std::vector<int> role_idx;

        query.prepare("select idx_property, value from db.person_data where idx_person = :idx;");
        query.bindValue(":idx", p.idx());
        if(!query.exec())
        {
            throw DatabaseException("select", "person_data", query.lastError().text().toStdString());
        }
        while (query.next())
        {
            switch (query.value(0).toInt())
            {
            case 1:
                p.birthday(query.value(1).toDate());
                break;
            case 2:
                p.birthplace(query.value(1).toString());
                break;
            case 3:
                p.email(query.value(1).toString());
                break;
            case 4:
                p.street(query.value(1).toString());
                break;
            case 5:
                p.street_number(query.value(1).toString());
                break;
            case 6:
                p.post(query.value(1).toString());
                break;
            case 7:
                p.postal_number(query.value(1).toString().toInt());
                break;
            case 8:
                p.country(query.value(1).toString());
                break;
            case 9:
                p.phone(query.value(1).toString());
                break;
            case 10:
                p.sex(query.value(1).toString() == "female");
                break;
            case 11:
                p.comment(query.value(1).toString());
                break;
            case 12:
                role_idx.emplace_back(query.value(1).toInt());
                break;
            default:
                throw DatabaseException("select", "person_data", "Unrecognised index: " + query.value(0).toString().toStdString());
            }
        }

        // roles
        for(auto it=role_idx.begin(); it!=role_idx.end(); ++it)
        {
            query.prepare("select value from db.role where idx = :idx;");
            query.bindValue(":idx", *it);
            if(!query.exec())
            {
                throw DatabaseException("select", "role", query.lastError().text().toStdString());
            }
            while (query.next())
            {
                p.roles().emplace_back(query.value(0).toString());
            }
        }
    }

    _db.close();
    return events;
}
