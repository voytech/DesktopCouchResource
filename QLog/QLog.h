#ifndef _QLOG_H
#define _QLOG_H


#include <QObject>
#include <QString>
#include <QDateTime>
#include <QFile>

/**
  This is very, but really very very very very very very very minimalistic logging "system :P"
 */
class QLog
{
private:
    static QLog* instance;
    QFile file;
    QLog();
public:
    enum Level
    {
        WARNING,
        ERROR,
        INFO,
    };
    static QLog* getLogger();
    ~QLog();
    void setOutput(const QString& filename);
    void log(const QString&,Level);
};
#endif
