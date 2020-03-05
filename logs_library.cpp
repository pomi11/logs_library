#include "logs_library.h"

LOG::LOG()
{
    date=QDateTime::currentDateTime();
}

LOG::LOG(std::string header,std::string message,std::vector<std::pair<std::string,std::string>> custom)
{
    date=QDateTime::currentDateTime();
    sHeader=header;
    sMessage=message;
    vCustoms=custom;
}

void LOG::add_custom(std::string tag, std::string message)
{
    vCustoms.push_back(std::pair<std::string,std::string>(tag,message));
}

void LOG::add_customs(std::vector<std::pair<std::string,std::string>> custom)
{
    foreach(auto item,custom)
    {
        vCustoms.push_back(item);
    }
}

void LOG::set_date(std::string date,std::string format)
{
    this->date=QDateTime::fromString(QString::fromStdString(date),QString::fromStdString(format));
}

LOGS::LOGS()
{

}
