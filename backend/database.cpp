#include "database.hpp"

#include <stdexcept>

Database::Database(QString path, std::shared_ptr<Logger> &logger) : _logger(logger)
{
    _db = QSqlDatabase::database();

    _folder = QFileInfo(path).absoluteDir().absolutePath();

    bool create = !QFileInfo(path).exists();
    _db.setDatabaseName(path);
    if(create)
    {
        create_database();
        _logger->log("Database " + path + " successfuly created");
    }

    _logger->log("Database " + path + " successfuly opened");
}

Database::~Database()
{
    // because, reasons
    _db = QSqlDatabase();
    _logger->log("Database closed");
}

void Database::create_database()
{
    _db.open();
    QSqlQuery query;

    // create tables
    if(!query.exec("CREATE TABLE person (idx integer primary key, name text not null, surname text not null);"))
    {
        _logger->log("Error creating person: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE person_property (idx integer primary key, property text not null);"))
    {
        _logger->log("Error creating person_property: " + query.lastError().text());
    }
    if(!query.exec("CREATE TABLE person_data (idx integer primary key, idx_person integer not null, "
               "idx_property integer not null, value text);"))
    {
        _logger->log("Error creating person_data: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE atendance (idx integer primary key, idx_person integer not null,"
               "idx_event integer not null, int leader not null);"))
    {
        _logger->log("Error creating atendance: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE event (idx integer primary key, name text not null, type text not null);"))
    {
        _logger->log("Error creating event: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE event_property (idx integer primary key, property text not null);"))
    {
        _logger->log("Error creating event_property: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE event_data (idx integer primary key, idx_event integer not null,"
               "idx_property integer not null, value text);"))
    {
        _logger->log("Error creating event_data: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE system_info (idx integer primary key, property text not null, value text not null);"))
    {
        _logger->log("Error creating system_info: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE roles (idx integer primary key, value text not null);"))
    {
        _logger->log("Error creating roles: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("CREATE TABLE family (idx integer primary key, value text not null);"))
    {
        _logger->log("Error creating family: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }


    // fill lookup tables
    if(!query.exec("INSERT INTO person_property VALUES"
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
               "(13, 'family');"))
    {
        _logger->log("Error creating family: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }

    if(!query.exec("INSERT INTO event_property VALUES"
               "(1, 'start_date'),"
               "(2, 'end_date'),"
               "(3, 'comment');"))
    {
        _logger->log("Error creating family: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }

    if(!query.exec("INSERT INTO system_info VALUES"
               "(1, 'program version', '0.1.0-beta'),"
               "(2, 'database version', '0.1.0-beta');"))
    {
        _logger->log("Error creating family: " + query.lastError().text());
        throw std::logic_error(query.lastError().text().toStdString());
    }

    _db.close();
    _logger->log("Database successfully created");
}

void Database::save_person(PersonEntity p)
{
    _db.open();
    QSqlQuery query;
    query.prepare("UPDATE person SET name = :name, surname= :surname where idx = :idx;");
    query.bindValue(":name", p.name());
    query.bindValue(":surname", p.surname());
    query.bindValue(":idx", p.idx());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    query.prepare("DELETE from person_data where idx_person = :idx;");
    query.bindValue(":idx", p.idx());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
}

int Database::insert_person(PersonEntity p)
{
    _db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO  person(name, surname) VALUES(:name, :surname);");
    query.bindValue(":name", p.name());
    query.bindValue(":surname", p.surname());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("SELECT last_insert_rowid();"))
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
    return idx;
}


std::vector<PersonBaseEntity> Database::person_list()
{
    _db.open();
    QSqlQuery query;
    std::vector<PersonBaseEntity> values;
    if(!query.exec("SELECT idx, name, surname FROM person;"))
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    while (query.next())
    {
        values.emplace_back(PersonBaseEntity(query.value(0).toInt(), query.value(1).toString(),  query.value(2).toString()));
    }
    _db.close();
    return values;
}

PersonEntity Database::get_person(int idx)
{
    if(idx==0) return PersonEntity();

    _db.open();

    PersonEntity p;
    QSqlQuery query;
    query.prepare("SELECT name, surname from person where idx = :idx;");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
        throw std::logic_error(query.lastError().text().toStdString());
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
    _db.close();
    return p;
}

void Database::delete_person(int idx)
{
    _db.open();
    QSqlQuery query;
    query.prepare("DELETE from person_data where idx_person = :idx");
    query.bindValue(":idx", idx);
    query.exec();
    query.prepare("DELETE from person where idx = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
}

void Database::insert_role(QString val)
{
    _db.open();
    QSqlQuery query;
    query.prepare("SELECT COUNT(value) from role where value = :val");
    query.bindValue(":val", val);
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    int tmp = 1;
    while (query.next())
    {
        tmp = query.value(0).toInt();
    }
    if(tmp == 0)
    {
        query.prepare("INSERT into role (value) VALUES (:val)");
        query.bindValue(":val", val);
        if(!query.exec())
        {
            throw std::logic_error(query.lastError().text().toStdString());
        }
    }
    _db.close();
}

void Database::save_event(EventEntity e)
{
    _db.open();
    QSqlQuery query;
    query.prepare("UPDATE event SET name = :name, type= :type where idx = :idx;");
    query.bindValue(":name", e.name());
    query.bindValue(":type", e.type());
    query.bindValue(":idx", e.idx());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    query.prepare("DELETE from event_data where idx_event = :idx;");
    query.bindValue(":idx", e.idx());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
}

EventEntity Database::get_event(int idx)
{
    _db.open();
    EventEntity e;
    QSqlQuery query;
    query.prepare("SELECT name, type from event where idx= :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
        throw std::logic_error(query.lastError().text().toStdString());
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
    _db.close();
    return e;
}

int Database::insert_event(EventEntity e)
{
    _db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO  event(name, type) VALUES(:name, :type);");
    query.bindValue(":name", e.name());
    query.bindValue(":type", e.type());
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    if(!query.exec("SELECT last_insert_rowid();"))
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
            throw std::logic_error(query.lastError().text().toStdString());
        }
    }
    else
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
    return idx;
}

std::vector<EventBaseEntity> Database::event_list()
{
    _db.open();
    QSqlQuery query;
    std::vector<EventBaseEntity> events;
    if(!query.exec("SELECT idx, name, type from event;"))
    {
        throw std::logic_error(query.lastError().text().toStdString());
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
    query.prepare("DELETE from event where idx = :idx");
    query.bindValue(":idx", idx);
    query.exec();
    query.prepare("DELETE from event_data where idx_event = :idx");
    query.bindValue(":idx", idx);
    if(!query.exec())
    {
        throw std::logic_error(query.lastError().text().toStdString());
    }
    _db.close();
}

QString Database::folder()
{
    return _folder;
}
