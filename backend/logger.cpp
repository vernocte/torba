#include "logger.hpp"
#include <QDir>
#include <QDebug>
#include <QDate>
#include <deque>
#include <algorithm>

Logger::Logger() : _file("logs/" + QDate::currentDate().toString("yyyyMMdd") + ".log")
{
    if(!QDir("logs").exists())
    {
        QDir().mkdir("logs");
    }
    _file.open(QIODevice::WriteOnly | QIODevice::Append);
    QStringList files = QDir("logs").entryList(QStringList("*.log"));
    std::deque<QDate> valid_logs;
    for(int i=0; i<files.length(); ++i)
    {
        QDate a = QDate::fromString(QFileInfo(files[i]).baseName(),"yyyyMMdd");
        if(a != QDate())
        {
            valid_logs.emplace_back(a);
        }
    }
    if(valid_logs.size()>MAX_LOGS)
    {
        std::sort(valid_logs.begin(), valid_logs.end());
        while(valid_logs.size()>MAX_LOGS)
        {
            if(valid_logs[0]!=QDate::currentDate())
            {
                QFile::remove("logs/" + valid_logs[0].toString("yyyyMMdd") + ".log");
            }
            valid_logs.pop_front();
        }
    }
    initiate();
}

Logger::~Logger()
{
    _file.close();
}

void Logger::initiate()
{
    _file.write("\r\n\r\n");
    _file.write("## NEW RUN ##");
    _file.write("\r\n\r\n");
    _file.flush();
}

void Logger::log(QString message)
{
    _file.write((QTime::currentTime().toString("HH.mm:ss") + ": " + message + "\r\n").toUtf8());
    _file.flush();
}
