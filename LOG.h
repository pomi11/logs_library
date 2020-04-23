#ifndef LOG_H
#define LOG_H

#include "logs_library_global.h"
#include <QDateTime>
#include <QMap>
#include <QDataStream>


class LOGS_LIBRARY_EXPORT LOG
{
private:
    QString header,message,type,format;
    QDateTime date;
   // QVector<std::pair<QString,QString>> vCustoms;
    QMap<QString,QString> map;

public:
    LOG();
    LOG(QDateTime date) {this->date=date;};
    LOG(QString header,QString message,QMap<QString,QString> custom);
    void set_message(QString message)   {this->message=message; map["message"]=message;};
    //void set_customs(QVector<std::pair<QString,QString>> custom) {vCustoms=custom;};
    void add_custom(QString tag, QString message);
    void add_customs(QMap<QString,QString> custom);
    void set_date(QString date,QString format);
    void set_date(QDateTime date)   {this->date=date; map["date"]=this->date.toString(format);};
    void set_date_format(QString format) {this->format=format;};
    void set_header(QString header) {this->header=header; map["header"]=header;};
    void set_type(QString type) {this->type=type; map["type"]=type;};
    QMap<QString,QString> get_val_map() {return map;};
    QString get_message() {return this->message;};
    QString get_date(QString format);
    QDateTime get_date();
    QString get_header() {return this->header;};
    QString get_type() {return this->type;};
    QString get_date_format() {return this->format;};
};

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,LOG &fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,LOG &fs);

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,QVector<LOG> &list);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,QVector<LOG> const &list);

#endif // LOG_H
