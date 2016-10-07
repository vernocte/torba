// include header
#include "personentity.hpp"

// ### constructors

// #### default constructor
PersonEntity::PersonEntity() : PersonBaseEntity(),
    _sex(false),
    _postal_number(1000),
    _birthday(1900, 1, 1),
    _birthplace(),
    _comment(),
    _country("Slovenija"),
    _email(),
    _phone(),
    _post(),
    _street(),
    _street_number(),
    _participated(),
    _lead() { }


// ### accessors

/*
#### get sex

[returns]: sex, false for male, true for female
*/
bool PersonEntity::sex() const
{
    return _sex;
}


/*
#### set sex

[val]: new value for sex, false for male, true for female
*/
void PersonEntity::sex(const bool& val)
{
    _sex=val;
}

/*
#### get postal number

[returns]: postal number
*/
int PersonEntity::postal_number() const
{
    return _postal_number;
}

/*
#### set postal number

[val]: new value for postal number
*/
void PersonEntity::postal_number(const int& val)
{
    _postal_number = val;
}

/*
#### get birthday

[returns]: birthday
*/
QDate PersonEntity::birthday() const
{
    return _birthday;
}

/*
#### set birthday

[val]: new value for birthday
*/
void PersonEntity::birthday(const QDate& val)
{
    _birthday = val;
}

/*
#### get birthplace

[returns]: birthplace
*/
QString PersonEntity::birthplace() const
{
    return _birthplace;
}

/*
#### set birthplace

[val]: new value for birthplace
*/
void PersonEntity::birthplace(const QString& val)
{
    _birthplace = val;
}

/*
#### get comment

[returns]: comment
*/
QString PersonEntity::comment() const
{
    return _comment;
}

/*
#### get country

[returns]: country
*/
void PersonEntity::comment(const QString& val)
{
    _comment = val;
}

/*
#### set country

[val]: country
*/
QString PersonEntity::country() const
{
    return _country;
}

/*
#### get email

[returns]: email
*/
void PersonEntity::country(const QString& val)
{
    _country = val;
}

/*
#### set email

[val]: new value for email
*/
QString PersonEntity::email() const
{
    return _email;
}

/*
#### set email

[val]: new value for email
*/
void PersonEntity::email(const QString& val)
{
    _email = val;
}

/*
#### get phone

[returns]: phone
*/
QString PersonEntity::phone() const
{
    return _phone;
}

/*
#### set phone

[val]: phone
*/
void PersonEntity::phone(const QString& val)
{
    _phone = val;
}

/*
#### get post

[returns]: post
*/
QString PersonEntity::post() const
{
    return _post;
}

/*
#### set post

[val]: post
*/
void PersonEntity::post(const QString& val)
{
    _post = val;
}

/*
#### get street

[returns]: street
*/
QString PersonEntity::street() const
{
    return _street;
}

/*
#### set street

[val]: new value for email
*/
void PersonEntity::street(const QString& val)
{
    _street = val;
}

/*
#### get street number

[returns]: street number
*/
QString PersonEntity::street_number() const
{
    return _street_number;
}

/*
#### set street number

[val]: street number
*/
void PersonEntity::street_number(const QString& val)
{
    _street_number = val;
}

/*
#### gets or sets participated

[returns]: reference to participated vector
*/
std::vector<EventBaseEntity>& PersonEntity::participated()
{
    return _participated;
}

/*
#### gets or sets lead

[returns]: reference to lead vector
*/
std::vector<EventBaseEntity>& PersonEntity::lead()
{
    return _lead;
}
