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

std::string XML::log(std::vector<std::map<QString,QString>> logs)
{
    QString result;
    result+="\n\t<LOGS>";

    for(size_t i=0;i<logs.capacity();i++)
    {
        result+="\n\t\t<LOG num=\""+QString::number(i+1)+"\">\n";
        for(auto it=logs.at(i).begin();it!=logs.at(i).end();it++)
        {
            QString tag = it->first;
            tag.remove(":");
            result+="\t\t   <"+tag+">  "+it->second+"  </"+tag+">\n";
        }
        result+="\t\t</LOG>\n";
    }

    result+="\t</LOGS>\n";
    return result.toStdString();
}

std::string XML::sys_info(std::map<QString,QString> sysInfo)
{
    QString result;
    result+="\n\t<SYSTEM_INFO>\n";

    for(auto it=sysInfo.begin();it!=sysInfo.end();it++)
    {
        QString tag = it->first;
        tag.remove(":");
        result+="\t\t<"+tag+">  "+it->second+"  </"+tag+">\n";
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

std::string TXT::log(std::vector<std::map<QString,QString>> logs)
{
    //std::string res = header.toStdString()+"\n \t"+date.toString("dd.MM.yyyy").toStdString()+" "+content.toStdString()+"\nTXT_LOG\n";
  //  return infos.at(0).toStdString();
}

std::string TXT::end_file()
{
    return "to jest endTXT";
}

/*FILE_STRUCT::FILE_STRUCT(std::string filePath,std::string header,std::string footer,std::vector<LOG> elements)
{
    this->filePath=filePath;
    this->header=header;
    this->footer=footer;
    this->elements=elements;
}

int FILE_STRUCT::write(char mode)
{
    QFile file(QString::fromStdString(filePath));

    file.open(QFileDevice::OpenModeFlag::Truncate | QFileDevice::OpenModeFlag::WriteOnly | QFile::Text);
    if(!file.isOpen())
    {
        std::cout<<"something_wrong";
        return -1;
    }
    file.write(header.c_str());
    if(newLineHeader)
        file.write("\n");

    std::string format = elements.begin()->get_date_format();

    std::cout<<"testowe"<<format;

    foreach(auto item,elements)
    {

        if(item.get_header()!="")
        {
            if(braces.first!="")
                file.write(braces.first.c_str());

            file.write(item.get_header().c_str());

            if(braces.second!="")
                file.write(braces.second.c_str());

            if(newLineElements)
                file.write("\n");
            else
                file.write("\t");
        }

        if(item.get_date(format)!="")
        {
            if(braces.first!="")
                file.write(braces.first.c_str());

            file.write(item.get_date(format).c_str());

            if(braces.second!="")
                file.write(braces.second.c_str());

            if(newLineElements)
                file.write("\n");
            else
                file.write("\t");
        }

        if(item.get_type()=="")
        {
            item.set_type("NORMAL");
        }

        if(braces.first!="")
            file.write(braces.first.c_str());

        file.write(item.get_type().c_str());

        if(braces.second!="")
            file.write(braces.second.c_str());

        if(newLineElements)
            file.write("\n");
        else
            file.write("\t");

        if(braces.first!="")
            file.write(braces.first.c_str());

        file.write(item.get_message().c_str());

        if(braces.second!="")
            file.write(braces.second.c_str());

        file.write("\n");
    }

    if(newLineFooter)
        file.write("\n");
    file.write(footer.c_str());

    file.close();
}
*/
