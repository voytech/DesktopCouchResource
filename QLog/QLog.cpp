#include "QLog.h"

QLog* QLog::instance = NULL;

QLog::QLog()
{
}
QLog::~QLog()
{

}

QLog* QLog::getLogger()
{
    if (!instance) instance = new QLog();
    return instance;
}
void QLog::setOutput(const QString& filename)
{
    file.setFileName(filename);
}
void QLog::log(const QString& mess, Level level)
{
    QString message;
    switch(level)
    {
    case INFO:
        message+="INFO";
        break;
    case WARNING:
        message+="WARNING";
        break;
    case ERROR:
        message+="ERROR";
        break;
    }
    QString date = QDateTime::currentDateTime().toString();
    message += " " + date + " ";
    message += mess+"\n";
    QByteArray barray;
    barray.append(message);
    file.open(QIODevice::Append);
    file.write(barray);
    file.close();
}

