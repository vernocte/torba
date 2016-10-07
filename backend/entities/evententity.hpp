#ifndef EVENTENTITY_HPP
#define EVENTENTITY_HPP

// parent
#include "eventbaseentity.hpp"

// qt library
#include<QDate>

// local include
#include "personbaseentity.hpp"

// # Event entity
class EventEntity : public EventBaseEntity
{
    // ## private
private:

    // ### fields

    // #### end date
    QDate _end_date;

    // #### start date
    QDate _start_date;

    // #### comment
    QString _comment;

    // #### leaders
    std::vector<PersonBaseEntity> _leaders;

    // #### participants
    std::vector<PersonBaseEntity> _participants;

    // ## public
public:

    // ### constructors

    // #### default constructor
    explicit EventEntity();

    // ### accessors

    /*
    #### get end date

    [returns]: end date
    */
    QDate end_date() const;

    /*
    #### set end date

    [val]: new value for end date
    */
    void end_date(const QDate& val);

    /*
    #### get start date

    [returns]: start date
    */
    QDate start_date() const;

    /*
    #### set start date

    [val]: new value for start date
    */
    void start_date(const QDate& val);
    /*
    #### get comment

    [returns]: comment
    */
    QString comment() const;

    /*
    #### set comment

    [val]: new value for comment
    */
    void comment(const QString& val);

    /*
    #### gets or sets leaders

    [returns]: reference to leaders
    */
    std::vector<PersonBaseEntity>& leaders();

    /*
    #### gets or sets participants

    [returns]: reference to participants
    */
    std::vector<PersonBaseEntity>& participants();
};

#endif // EVENTENTITY_HPP
