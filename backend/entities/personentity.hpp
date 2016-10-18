#ifndef PERSON_HPP
#define PERSON_HPP

// parent
#include "personbaseentity.hpp"

// standard library
#include <vector>

// qt library
#include <QDate>

// local includes
#include "eventbaseentity.hpp"

// # person entity
class PersonEntity : public PersonBaseEntity
{
    // ## private
private:

    // ### fields

    // #### sex
    bool _sex;

    // #### postal number
    int _postal_number;

    // #### birthday
    QDate _birthday;

    // #### birthplace
    QString _birthplace;

    // #### comment
    QString _comment;

    // #### country
    QString _country;

    // #### email
    QString _email;

    // #### phone
    QString _phone;

    // #### post
    QString _post;

    // #### street
    QString _street;

    // #### street number
    QString _street_number;

    // #### participated
    std::vector<EventBaseEntity> _participated;

    // #### lead
    std::vector<EventBaseEntity> _lead;

    // ## public
public:

    // ### constructors

    // #### default constructor
    explicit PersonEntity();

    // ### accessors

    /*
    #### get sex

    [returns]: sex, false for male, true for female
    */
    bool sex() const;

    /*
    #### set sex

    [val]: new value for sex, false for male, true for female
    */
    void sex(const bool& val);

    /*
    #### get postal number

    [returns]: postal number
    */
    int postal_number() const;

    /*
    #### set postal number

    [val]: new value for postal number
    */
    void postal_number(const int& val);

    /*
    #### get birthday

    [returns]: birthday
    */
    QDate birthday() const;

    /*
    #### set birthday

    [val]: new value for birthday
    */
    void birthday(const QDate& val);

    /*
    #### get birthplace

    [returns]: birthplace
    */
    QString birthplace() const;

    /*
    #### set birthplace

    [val]: new value for birthplace
    */
    void birthplace(const QString& val);

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
    #### get country

    [returns]: country
    */
    QString country() const;

    /*
    #### set country

    [val]: country
    */
    void country(const QString& val);

    /*
    #### get email

    [returns]: email
    */
    QString email() const;

    /*
    #### set email

    [val]: new value for email
    */
    void email(const QString& val);

    /*
    #### get phone

    [returns]: phone
    */
    QString phone() const;

    /*
    #### set phone

    [val]: phone
    */
    void phone(const QString& val);

    /*
    #### get post

    [returns]: post
    */
    QString post() const;

    /*
    #### set post

    [val]: post
    */
    void post(const QString& val);

    /*
    #### get street

    [returns]: street
    */
    QString street() const;

    /*
    #### set street

    [val]: new value for email
    */
    void street(const QString& val);

    /*
    #### get street number

    [returns]: street number
    */
    QString street_number() const;

    /*
    #### set street number

    [val]: street number
    */
    void street_number(const QString& val);

    /*
    #### gets or sets participated

    [returns]: reference to participated vector
    */
    std::vector<EventBaseEntity>& participated();

    /*
    #### gets participated

    [returns]: const reference to participated vector
    */
    const std::vector<EventBaseEntity>& participated() const;

    /*
    #### gets or sets lead

    [returns]: reference to lead vector
    */
    std::vector<EventBaseEntity>& lead();

    /*
    #### gets lead

    [returns]: const reference to lead vector
    */
    const std::vector<EventBaseEntity>& lead() const;
};

#endif // PERSON_HPP
