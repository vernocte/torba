#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QtSql>
#include <QString>

#include "entities/personentity.hpp"
#include "entities/evententity.hpp"
#include "logger.hpp"

#include<memory>

class Database
{
private:

    QSqlDatabase _db;
    std::shared_ptr<Logger> _logger;

    void create_database();

public:

    Database(QString path, std::shared_ptr<Logger> &logger);

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
