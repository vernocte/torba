// include header
#include "personbaseentity.hpp"

// ### constructors

// #### default constructor
PersonBaseEntity::PersonBaseEntity() :
    _idx(0), _name(), _surname() { }

/*
#### values constructor

[idx]: idx
[name]: name
[surname]: surname
*/
PersonBaseEntity::PersonBaseEntity(const int &idx, const QString& name,
                                   const QString& surname) :
    _idx(idx), _name(name), _surname(surname) { }

// ### accessors

/*
#### get idx

[returns]: idx
*/
int PersonBaseEntity::idx() const
{
    return _idx;
}

/*
#### set idx

[val]: new value for idx
*/
void PersonBaseEntity::idx(const int& val)
{
    _idx=val;
}

/*
#### get name

[returns]: name
*/
QString PersonBaseEntity::name() const
{
    return _name;
}

/*
#### set name

[val]: new value for name
*/
void PersonBaseEntity::name(const QString& val)
{
    _name=val;
}

/*
#### get surname

[returns]: surname
*/
QString PersonBaseEntity::surname() const
{
    return _surname;
}

/*
#### set surname

[val]: new value for surname
*/
void PersonBaseEntity::surname(const QString& val)
{
    _surname = val;
}
