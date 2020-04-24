#include "log.h"

LOG::LOG()
{
    date=QDateTime::currentDateTime();
    format="dd.MM.yyyy hh:mm:ss";
    si.disable_all();
}

LOG::LOG(QString header,QString message,QMap<QString,QString> custom)
{
    date=QDateTime::currentDateTime();
    this->header=header;
    this->message=message;
    format="dd.MM.yyyy hh:mm:ss";
    si.disable_all();
    //this->add_customs(custom);
    //si = nullptr;
}

/*void LOG::add_custom(QString tag, QString message)
{
   // customs[tag]=message;
}

void LOG::add_customs(QMap<QString,QString> custom)
{
    for(auto it = custom.begin();it!=custom.end();it++)
    {
   //     customs[it.key()]=it.value();
    }
}*/

void LOG::set_date(QString date,QString format)
{
    this->format=format;
    this->date=QDateTime::fromString((date),format);
   // basic["date"]=this->date.toString(format);
}

QString LOG::get_date(QString format)
{
    return this->date.toString(format);
}

QDateTime LOG::get_date()
{
    return this->date;
}

QMap<QString,QString> LOG::get_basic()
{
    QMap<QString,QString> basic;
    if(header!="")
        basic["header"]=header;

    basic["message"]=message;
    basic["date"]=date.toString(format);
    basic["type"]=type;

    return basic;
}

QMap<QString,QString> LOG::get_sys_info_map()
{
    return si.get_info_map();
}

QDataStream& operator>>(QDataStream& in,LOG & fs)
{
    QString header,message,type,format;
    QDateTime date;
   // QVector<std::pair<QString,QString>> vCustoms;
   // QMap<QString,QString> map;
    SYS_INFO si;
    in>>header;
    in>>message;
    in>>type;
    in>>format;
    in>>date;
    in>>si;
  //  in>>map;
    fs = LOG();
    fs.set_header(header);
    fs.set_message(message);
    fs.set_type(type);
    fs.set_date_format(format);
    fs.set_date(date);
    fs.add_sys_info(si);

    return in;
}

QDataStream& operator<<(QDataStream& out,LOG &fs)
{
    out<<fs.get_header();
    out<<fs.get_message();
    out<<fs.get_type();
    out<<fs.get_date_format();
    out<<fs.get_date();
    out<<fs.get_sys_info();

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
