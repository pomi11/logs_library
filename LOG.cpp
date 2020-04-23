#include "log.h"

LOG::LOG()
{
    date=QDateTime::currentDateTime();
    format="dd.MM.yyyy hh:mm:ss";
}

LOG::LOG(QString header,QString message,QMap<QString,QString> custom)
{
    date=QDateTime::currentDateTime();
    this->header=header;
    map["header"]=header;
    this->message=message;
    map["message"]=message;
    format="dd.MM.yyyy hh:mm:ss";
    map["date"]=date.toString(format);
    this->add_customs(custom);
}

void LOG::add_custom(QString tag, QString message)
{
    map[tag]=message;
}

void LOG::add_customs(QMap<QString,QString> custom)
{
    for(auto it = custom.begin();it!=custom.end();it++)
    {
        map[it.key()]=it.value();
    }
}

void LOG::set_date(QString date,QString format)
{
    this->format=format;
    this->date=QDateTime::fromString((date),format);
    map["date"]=this->date.toString(format);
}

QString LOG::get_date(QString format)
{
    return this->date.toString(format);
}

QDateTime LOG::get_date()
{
    return this->date;
}

QDataStream& operator>>(QDataStream& in,LOG & fs)
{
    QString header,message,type,format;
    QDateTime date;
   // QVector<std::pair<QString,QString>> vCustoms;
   // QMap<QString,QString> map;
    in>>header;
    in>>message;
    in>>type;
    in>>format;
    in>>date;
  //  in>>map;
    fs = LOG();
    fs.set_header(header);
    fs.set_message(message);
    fs.set_type(type);
    fs.set_date_format(format);
    fs.set_date(date);
    return in;
}

QDataStream& operator<<(QDataStream& out,LOG &fs)
{
    out<<fs.get_header();
    out<<fs.get_message();
    out<<fs.get_type();
    out<<fs.get_date_format();
    out<<fs.get_date();
 //   out<<fs.get_val_map();

    return out;
}

QDataStream& operator>>(QDataStream& in,QVector<LOG> &list)
{
    int a = 0;
    in >> a;
    for(int i=0;i<a;i++)
    {
        LOG dss;
        in>>dss;
        list.push_back(dss);
    }
    return in;
}

QDataStream& operator<<(QDataStream& out,QVector<LOG> const &list)
{
    out<<list.size();
    for(LOG d : list)
        out<<d;
    return out;

}
