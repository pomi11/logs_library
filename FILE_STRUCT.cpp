#include "file_struct.h"
#include <QFile>

XML::XML()
{

}

XML::XML(QString, QString)
{

}

std::string XML::start_file(QString description)
{
    QString result;
    result+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    result+="<FILE>\n";
    result+="\n\t<FILE_CREATION_DATE>"+QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")+"</FILE_CREATION_DATE>\n";
    if(description!="")
        result+="\t<FILE_DESCR>"+description+"</FILE_DESCR>\n";
    return result.toStdString();
}

std::string XML::log(QVector<QMap<QString,QString>> logs)
{
    QString result;
    result+="\n\t<LOGS>";

    for(int i=0;i<logs.count();i++)
    {
        result+="\n\t\t<LOG num=\""+QString::number(i+1)+"\">\n";
        for(auto it=logs.at(i).begin();it!=logs.at(i).end();it++)
        {
            QString tag = it.key();
            tag.remove(":");
            result+="\t\t   <"+tag+">  "+it.value()+"  </"+tag+">\n";
        }
        result+="\t\t</LOG>\n";
    }

    result+="\t</LOGS>\n";
    return result.toStdString();
}

std::string XML::sys_info(QMap<QString,QString> sysInfo)
{
    QString result;
    result+="\n\t<SYSTEM_INFO>\n";

    for(auto it=sysInfo.begin();it!=sysInfo.end();it++)
    {
        QString tag = it.key();
        tag.remove(":");
        result+="\t\t<"+tag+">  "+it.value()+"  </"+tag+">\n";
    }

    result+="\t</SYSTEM_INFO>\n";
    return result.toStdString();
}

std::string XML::end_file()
{
    return "\n</FILE>";
}

TXT::TXT()
{

}

TXT::TXT(QString, QString)
{

}

std::string TXT::start_file(QString description)
{
    return "to jest startTXT\n";
}

std::string TXT::log(QVector<QMap<QString,QString>> logs)
{
    //std::string res = header.toStdString()+"\n \t"+date.toString("dd.MM.yyyy").toStdString()+" "+content.toStdString()+"\nTXT_LOG\n";
  //  return infos.at(0).toStdString();
}

std::string TXT::end_file()
{
    return "to jest endTXT";
}

QDataStream& operator>>(QDataStream& in,XML *& fs)
{

    //std::string s_login, s_fileName,s_path,s_mainHeader,s_header,s_format,s_footer,s_type;
    QVector<QString> tags;
    bool isNumLog,isSysSum,isFileDescr,isFileDate;
    in >>tags;
    in>>isNumLog;
    in>>isSysSum;
    in>>isFileDescr;
    in>>isFileDate;
    // qDebug()<<fullPath;
    fs = new XML();
    fs->set_tags(tags);
    fs->show_num_log(isNumLog);
    fs->show_sys_info(isSysSum);
    fs->show_file_descr(isFileDescr);
    fs->show_file_date(isFileDate);

    return in;
}

QDataStream& operator<<(QDataStream& out,XML &fs)
{
    out<<fs.get_tags();
    out<<fs.is_num_log();
    out<<fs.is_sys_info();
    out<<fs.is_file_descr();
    out<<fs.is_file_date();
    return out;
}
