#include "file_struct.h"
#include <QFile>

XML::XML()
{

}

XML::XML(QString, QString)
{

}

std::string XML::start_file()
{
    return "to jest startXML\n";
}

std::string XML::log(QString header,QString content, QDateTime date)
{
    std::string res = header.toStdString()+"\n \t"+date.toString("dd.MM.yyyy").toStdString()+" "+content.toStdString()+"\nXML_LOG\n";
    return res;
}

std::string XML::end_file()
{
    return "to jest endXML";
}

TXT::TXT()
{

}

TXT::TXT(QString, QString)
{

}

std::string TXT::start_file()
{
    return "to jest startTXT\n";
}

std::string TXT::log(QString header,QString content, QDateTime date)
{
    std::string res = header.toStdString()+"\n \t"+date.toString("dd.MM.yyyy").toStdString()+" "+content.toStdString()+"\nTXT_LOG\n";
    return res;
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
