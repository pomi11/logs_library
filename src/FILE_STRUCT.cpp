#include "include/FILE_STRUCT.h"
#include <QFile>

XML::XML()
{

}

/*XML::XML(QString, QString)
{

}*/

std::string XML::start_file(QString description)
{
    QString result;
    result+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    result+="<FILE>\n";
    result+="\n\t<FILE_CREATION_DATE>"+QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")+"</FILE_CREATION_DATE>\n";
    if(description!="")
        result+="\t<FILE_DESCR>"+description+"</FILE_DESCR>\n";
    result+="\n\t<LOGS>";
    return result.toStdString();
}

std::string XML::log(QVector<QMap<QString,QMap<QString,QString>>> logs)
{
    QString result="";

    for(int i=0;i<logs.count();i++)
    {
        QString tmp="";
        //result+="\n\t\t<LOG";
        tmp+="\n\t\t<LOG";

        if(!showLogHeader)
            logs[i]["basic"].remove("header");

        if(!showLogDate)
            logs[i]["basic"].remove("date");

        if(showLogNumber)
            //result+=" num=\""+QString::number(i+1)+"\"";
            tmp+=" num=\""+QString::number(i)+"\"";

        if(showLogType)
        {
            QString type=logs[i]["basic"]["type"];
            if(type=="SYSTEM_INFO" && !showSysSummary)
                continue;
            logs[i]["basic"].remove("type");
            //result+=" type=\""+type+"\"";
            tmp+=" type=\""+type+"\"";
        }

        result+=tmp+">\n";

        for(auto it=logs[i]["basic"].begin();it!=logs[i]["basic"].end();it++)
        {
           // if(it.key()=="type")
             //   continue;
            QString tag = it.key();
            tag.remove(":");
            result+="\t\t   <"+tag+">  "+it.value()+"  </"+tag+">\n";
        }
        logs[i].remove("basic");

        for(auto it=logs[i].begin();it!=logs[i].end();it++)
        {
           /* if(it.key()=="basic")
                continue;*/
            if(it->count()<1)
                continue;
            QString tag = it.key();
            result+="\t\t   <"+tag+">\n";
            for(auto it2=it->begin();it2!=it->end();it2++)
            {
                QString tag2 = it2.key();
                tag2.remove(":");
                result+="\t\t\t   <"+tag2+">  "+it2.value()+"  </"+tag2+">\n";
            }
            result+="\t\t   </"+tag+">\n";
        }


        result+="\t\t</LOG>\n";
    }
    return result.toStdString();
}
/*
std::string XML::sys_info(QMap<QString,QString> sysInfo)
{
    if(!showSysSummary)
        return "\n\t<LOGS>";
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
*/
std::string XML::end_file()
{
    QString result="\t</LOGS>\n";
    result+="\n</FILE>";
    return result.toStdString();
}

/*TXT::TXT()
{

}

TXT::TXT(QString, QString)
{

}

std::string TXT::start_file(QString description)
{
    return "to jest startTXT\n";
}

std::string TXT::log(QVector<QMap<QString,QMap<QString,QString>>> logs)
{
    //std::string res = header.toStdString()+"\n \t"+date.toString("dd.MM.yyyy").toStdString()+" "+content.toStdString()+"\nTXT_LOG\n";
    //  return infos.at(0).toStdString();
}

std::string TXT::end_file()
{
    return "to jest endTXT";
}*/
