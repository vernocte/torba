#ifndef PERSONBASEENTITY_HPP
#define PERSONBASEENTITY_HPP


// qt library
#include <QString>

// # Person base entity
class PersonBaseEntity
{
    // ## protected
protected:

    // ### fields

    // #### idx
    int _idx;

    // #### name
    QString _name;

    // #### surname
    QString _surname;

    // ## public
public:

    // ### constructors

    // #### default constructor
    PersonBaseEntity();

    /*
    #### values constructor

    [idx]: idx
    [name]: name
    [surname]: surname
    */
    PersonBaseEntity(const int& idx, const QString& name,
                     const QString& surname);

    // ### accessors

    /*
    #### get idx

    [returns]: idx
    */
    int idx() const;

    /*
    #### set idx

    [val]: new value for idx
    */
    void idx(const int& val);

    /*
    #### get name

    [returns]: name
    */
    QString name() const;

    /*
    #### set name

    [val]: new value for name
    */
    void name(const QString& val);

    /*
    #### get surname

    [returns]: surname
    */
    QString surname() const;

    /*
    #### set surname

    [val]: new value for surname
    */
    void surname(const QString& val);

};

#endif // PERSONBASEENTITY_HPP
