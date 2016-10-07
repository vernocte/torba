#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QtSql>
#include <QString>

#include "../backend/entities/personentity.hpp"
#include "../backend/entities/evententity.hpp"

class Database
{
private:
    QSqlDatabase _db;
    void create_database();
public:
    Database(QString path);
    Database();
    ~Database();
    bool save_person(PersonEntity p);
    PersonEntity get_person(int idx);
    int insert_person(PersonEntity p);
    std::vector<PersonBaseEntity> person_list();
    void delete_person(int idx);

    bool save_event(EventEntity e);
    EventEntity get_event(int idx);
    int insert_event(EventEntity e);
    std::vector<EventBaseEntity> event_list();
    void delete_event(int idx);

    void insert_role(QString val);
};

#endif // DATABASE_HPP
