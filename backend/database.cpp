#include "database.hpp"

#include <QDebug>

Database::Database()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
}

Database::Database(QString path)
{
    _db = QSqlDatabase::database();
    bool create = !QFileInfo(path).exists();
    _db.setDatabaseName(path);
    if(create)
    {
        create_database();
    }
}

Database::~Database()
{
    _db.close();

    // because, reasons
    _db = QSqlDatabase();
}

void Database::create_database()
{
    if(!_db.open()) throw;
    QSqlQuery query;

    // create tables
    query.exec("CREATE TABLE person (idx integer primary key, name text not null, surname text not null);");
    query.exec("CREATE TABLE person_property (idx integer primary key, property text not null);");
    query.exec("CREATE TABLE person_data (idx integer primary key, idx_person integer not null, "
               "idx_property integer not null, value text not null);");
    query.exec("CREATE TABLE atendance (idx integer primary key, idx_person integer not null,"
               "idx_event integer not null, int leader not null);");
    query.exec("CREATE TABLE event (idx integer primary key, name text not null, type text not null);");
    query.exec("CREATE TABLE event_property (idx integer primary key, property text not null);");
    query.exec("CREATE TABLE event_data (idx integer primary key, idx_event integer not null,"
               "idx_property integer not null, value text not null);");
    query.exec("CREATE TABLE system_info (idx integer primary key, property text not null, value text not null);");
    query.exec("CREATE TABLE roles (idx integer primary key, value text not null);");
    query.exec("CREATE TABLE family (idx integer primary key, value text not null);");


    // fill lookup tables
    query.exec("INSERT INTO person_property VALUES"
               "(1, 'birthday'),"
               "(2, 'birthplace'),"
               "(3, 'email'),"
               "(4, 'street'),"
               "(5, 'street_number'),"
               "(6, 'post'),"
               "(7, 'postal_number'),"
               "(8, 'country'),"
               "(9, 'phone'),"
               "(10, 'sex'),"
               "(11, 'comment'),"
               "(12, 'role'),"
               "(13, 'family');");

    query.exec("INSERT INTO event_property VALUES"
               "(1, 'start_date'),"
               "(2, 'end_date'),"
               "(3, 'comment');");

    query.exec("INSERT INTO system_info VALUES"
               "(1, 'program version', '0.1.0-beta'),"
               "(2, 'database version', '0.1.0-beta');");
}

bool Database::save_person(PersonEntity p)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("UPDATE person SET name = :name, surname= :surname where idx = :idx;");
    query.bindValue(":name", p.name());
    query.bindValue(":surname", p.surname());
    query.bindValue(":idx", p.idx());
    if(!query.exec())
    {
        return false;
    }
    query.prepare("DELETE from person_data where idx_person = :idx;");
    query.bindValue(":idx", p.idx());
    if(!query.exec())
    {
        return false;
    }
    query.prepare("INSERT INTO person_data (idx_person, idx_property, value) VALUES"
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
    query.bindValue(":idx", p.idx());
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
        return false;
    }
    return true;
}

int Database::insert_person(PersonEntity p)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("INSERT INTO  person(name, surname) VALUES(:name, :surname);");
    query.bindValue(":name", p.name());
    query.bindValue(":surname", p.surname());
    if(!query.exec())
    {
        return 0;
    }
    if(!query.exec("SELECT last_insert_rowid();"))
    {
        qDebug() << 2;
        return 0;
    }
    int idx = 0;

    while (query.next())
    {
        idx = query.value(0).toInt();
    }
    query.prepare("INSERT INTO person_data (idx_person, idx_property, value) VALUES"
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
        qDebug() << 3;
        return 0;
    }

    return idx;
}


std::vector<PersonBaseEntity> Database::person_list()
{
    if(!_db.open()) throw;
    QSqlQuery query;
    std::vector<PersonBaseEntity> values;
    if(!query.exec("SELECT idx, name, surname FROM person;"))
    {
        return values;
    }
    while (query.next())
    {
        values.emplace_back(PersonBaseEntity(query.value(0).toInt(), query.value(1).toString(),  query.value(2).toString()));
    }
    return values;
}

PersonEntity Database::get_person(int idx)
{
    if(idx==0) return PersonEntity();

    if(!_db.open()) throw;
    PersonEntity p;
    QSqlQuery query;
    query.prepare("SELECT name, surname from person where idx = :idx;");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        return p;
    }
    while (query.next())
    {
        p.name(query.value(0).toString());
        p.surname(query.value(1).toString());
    }
    p.idx(idx);
    query.prepare("SELECT idx_property, value from person_data where idx_person = :idx;");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        return PersonEntity();
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
        default:
            break;
        }
    }
    return p;
}

void Database::delete_person(int idx)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("DELETE from person_data where idx_person = :idx");
    query.bindValue(":idx", idx);
    query.exec();
    query.prepare("DELETE from person where idx = :idx");
    query.bindValue(":idx", idx);
    query.exec();
}

void Database::insert_role(QString val)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("SELECT COUNT(value) from role where value = :val");
    query.bindValue(":val", val);
    query.exec();
    int tmp = 1;
    while (query.next())
    {
        tmp = query.value(0).toInt();
    }
    if(tmp == 0)
    {
        query.prepare("INSERT into role (value) VALUES (:val)");
        query.bindValue(":val", val);
        query.exec();
    }
}

bool Database::save_event(EventEntity e)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("UPDATE event SET name = :name, type= :type where idx = :idx;");
    query.bindValue(":name", e.name());
    query.bindValue(":type", e.type());
    query.bindValue(":idx", e.idx());
    if(!query.exec())
    {
        return false;
    }
    query.prepare("DELETE from event_data where idx_event = :idx;");
    query.bindValue(":idx", e.idx());
    if(!query.exec())
    {
        return false;
    }
    query.prepare("INSERT INTO event_data (idx_event, idx_property, value) VALUES"
                  "(:idx, 1, :start_date),"
                  "(:idx, 2, :end_date),"
                  "(:idx, 3, :comment);");
    query.bindValue(":idx", e.idx());
    query.bindValue(":start_date", e.start_date().toString("yyyy-MM-dd"));
    query.bindValue(":end_date", e.end_date().toString("yyyy-MM-dd"));
    query.bindValue(":comment", e.comment());

    if(!query.exec())
    {
        return false;
    }
    return true;
}

EventEntity Database::get_event(int idx)
{
    if(!_db.open()) throw;
    EventEntity e;
    QSqlQuery query;
    query.prepare("SELECT name, type from event where idx= :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        return e;
    }
    while(query.next())
    {
        e.name(query.value(0).toString());
        e.type(query.value(1).toString());
    }

    query.prepare("SELECT idx_property, value from event_data where idx_event = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        return e;
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
    return e;
}

int Database::insert_event(EventEntity e)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("INSERT INTO  event(name, type) VALUES(:name, :type);");
    query.bindValue(":name", e.name());
    query.bindValue(":type", e.type());
    if(!query.exec())
    {
        return 0;
    }
    if(!query.exec("SELECT last_insert_rowid();"))
    {
        return 0;
    }
    int idx = 0;

    while (query.next())
    {
        idx = query.value(0).toInt();
    }
    if(idx!=0)
    {
        query.prepare("INSERT into event_data (idx_event, idx_property, value) VALUES"
                      "(:idx, 1, :start_date),"
                      "(:idx, 2, :end_date),"
                      "(:idx, 3, :comment);");
        query.bindValue(":idx", idx);
        query.bindValue(":start_date", e.start_date().toString("yyyy-MM-dd"));
        query.bindValue(":end_date", e.end_date().toString("yyyy-MM-dd"));
        query.bindValue(":comment", e.comment());
        if(!query.exec())
        {
            return 0;
        }
        return idx;
    }
    return 0;
}

std::vector<EventBaseEntity> Database::event_list()
{
    if(!_db.open()) throw;
    QSqlQuery query;
    std::vector<EventBaseEntity> events;
    if(!query.exec("SELECT idx, name, type from event;"))
    {
        return events;
    }
    while(query.next())
    {
        EventBaseEntity e;
        e.idx(query.value(0).toInt());
        e.name(query.value(1).toString());
        e.type(query.value(2).toString());
        events.emplace_back(e);
    }
    return events;
}

void Database::delete_event(int idx)
{
    if(!_db.open()) throw;
    QSqlQuery query;
    query.prepare("DELETE from event where idx = :idx");
    query.bindValue(":idx", idx);
    query.exec();
    query.prepare("DELETE from event_data where idx_event = :idx");
    query.bindValue(":idx", idx);
    query.exec();
}
