// include header
#include "eventbaseentity.hpp"

// ### constructors

// #### default constructor
EventBaseEntity::EventBaseEntity() :
    _idx(0), _name(), _type() { }

// ### accessors

/*
#### get idx

[returns]: idx
*/
int EventBaseEntity::idx() const
{
    return _idx;
}

/*
#### set idx

[val]: new value for idx
*/
void EventBaseEntity::idx(const int& val)
{
    _idx = val;
}

/*
#### get name

[returns]: name
*/
QString EventBaseEntity::name() const
{
    return _name;
}

/*
#### set name

[val]: new value for name
*/
void EventBaseEntity::name(const QString& val)
{
    _name = val;
}

/*
#### get type

[returns]: type
*/
QString EventBaseEntity::type() const
{
    return _type;
}

/*
#### set type

[val]: new value for type
*/
void EventBaseEntity::type(const QString& val)
{
    _type = val;
}
