#ifndef DATABASE_HPP
#define DATABASE_HPP

#include<memory>

#include <QtSql>
#include <QString>

#include "entities/personentity.hpp"
#include "entities/evententity.hpp"
#include "logger.hpp"

// # Database
class Database
{
    // ## Private
private:

    // ### Fields

    // #### Sqlite Database
    QSqlDatabase _db;

    // #### Logger
    std::shared_ptr<Logger> _logger;

    // #### Folder for database
    QString _path;

    // ### Private functions

    // #### Create database
    void create_database();

public:

    // ### Constructors

    // #### File and logger constructor
    Database(QString path, std::shared_ptr<Logger> &logger);

    // ### Destructor
    ~Database();

    // ### Accessors

    /*
    #### Folder

    [returns]: folder database is in
    */
    QString folder() const;
    QString path() const;

    // ### Person functions

    /*
    #### insert person

    [p]: person to insert
    [returns]: index of inserted person
    */
    int insert_person(const PersonEntity &p);

    /*
    #### delete person

    [p]: person to insert
    [returns]: index of inserted person
    */
    void delete_person(int idx);

    /*
    #### save person

    [p]: person to save
    */
    void save_person(const PersonEntity &p);

    /*
    #### get person

    [idx]: index of person
    [returns]: person with given index
    */
    PersonEntity get_person(int idx);

    /*
    #### get list of persons

    [idx]: index of person
    [returns]: person with given index
    */
    std::vector<PersonBaseEntity> person_list();

    // ### Event functions
    void save_event(EventEntity e);
    EventEntity get_event(int idx);
    int insert_event(EventEntity e);
    std::vector<EventBaseEntity> event_list();
    void delete_event(int idx);

    // ### category

    /*
    #### categories list

    [returns]: vector containing all categories
    */
    QStringList categories_list();

    /*
    #### add category

    [category]: category to add
    */
    void add_category(const QString& category);

    void export_database(const std::vector<int>& index, const QString& path);
};

#endif // DATABASE_HPP
