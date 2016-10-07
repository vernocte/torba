#ifndef EVENTBASEENTITY_HPP
#define EVENTBASEENTITY_HPP

// qt libraries
#include <QString>

// # Event base entity
class EventBaseEntity
{
    // ## protected
protected:

    // ### fields

    // #### idx
    int _idx;

    // #### name
    QString _name;

    // #### type
    QString _type;

    // ## public
public:

    // ### constructors

    // #### default constructor
    explicit EventBaseEntity();

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
    #### get type

    [returns]: type
    */
    QString type() const;

    /*
    #### set type

    [val]: new value for type
    */
    void type(const QString& val);
};

#endif // EVENTBASEENTITY_HPP
