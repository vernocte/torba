#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>
#include <QString>
#include <string>

class Logger
{
private:
    const unsigned int MAX_LOGS = 4;
    QFile _file;
    void initiate();

public:
    explicit Logger();
    virtual ~Logger();
    void log(const QString &message);
};

#endif // LOGGER_HPP
