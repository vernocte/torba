#ifndef FILTERENTITY_HPP
#define FILTERENTITY_HPP

#include <QDate>

class FilterEntity
{
private:

    bool _use_events;
    bool _use_category;
    bool _use_birth;

    std::vector<int> _events;
    QString _event_type;
    QString _person_category;
    QDate _born_from;
    QDate _born_to;

public:

    FilterEntity() : _use_events(false), _use_category(false), _use_birth(false), _events(), _event_type(), _person_category(), _born_from(), _born_to() { }
    bool use_events() const { return _use_events; }
    void use_events(bool val) { _use_events = val; }

    bool use_category() const { return _use_category; }
    void use_category(bool val) { _use_category = val; }

    bool use_birth() const { return _use_birth; }
    void use_birth(bool val) { _use_birth = val; }

    std::vector<int>& events() { return _events;}
    const std::vector<int>& events() const { return _events;}

    QString event_type() const { return _event_type; }
    void event_type(const QString& val) { _event_type = val; }

    QString person_category() const { return _person_category; }
    void person_category(const QString& val) { _person_category = val; }

    QDate born_from() const { return _born_from; }
    void born_from(const QDate& val) { _born_from = val; }

    QDate born_to() const { return _born_to; }
    void born_to(const QDate& val) { _born_to = val; }
};

#endif // FILTERENTITY_HPP
