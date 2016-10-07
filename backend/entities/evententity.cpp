// include header
#include "evententity.hpp"

// ### constructors

// #### default constructor
EventEntity::EventEntity() : EventBaseEntity(),
    _end_date(QDate::currentDate().addDays(2)),
    _start_date(QDate::currentDate()),
    _comment(),
    _leaders(),
    _participants() { }

// ### accessors

/*
#### get end date

[returns]: end date
*/
QDate EventEntity::end_date() const
{
    return _end_date;
}

/*
#### set end date

[val]: new value for end date
*/
void EventEntity::end_date(const QDate& val)
{
    _end_date = val;
}

/*
#### get start date

[returns]: start date
*/
QDate EventEntity::start_date() const
{
    return _start_date;
}

/*
#### set start date

[val]: new value for start date
*/
void EventEntity::start_date(const QDate& val)
{
    _start_date = val;
}

/*
#### get comment

[returns]: comment
*/
QString EventEntity::comment() const
{
    return _comment;
}

/*
#### set comment

[val]: new value for comment
*/
void EventEntity::comment(const QString& val)
{
    _comment = val;
}

/*
#### gets or sets leaders

[returns]: reference to leaders
*/
std::vector<PersonBaseEntity>& EventEntity::leaders()
{
    return _leaders;
}

/*
#### gets or sets participants

[returns]: reference to participants
*/
std::vector<PersonBaseEntity>& EventEntity::participants()
{
    return _participants;
}
