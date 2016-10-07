#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>

class Logger
{
private:
    const unsigned int MAX_LOGS = 4;
    QFile _file;
    void initiate();

public:
    explicit Logger();
    virtual ~Logger();
    void log(QString message);
};

#endif // LOGGER_HPP
