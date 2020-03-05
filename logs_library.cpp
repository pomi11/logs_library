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

std::string LOG::get_date(std::string format)
{
    return this->date.toString(QString::fromStdString(format)).toStdString();
}

QDateTime LOG::get_date()
{
    return this->date;
}

LOGS::LOGS()
{

}

void LOGS::add(LOG log)
{
    this->logs.push_back(log);
}

void LOGS::add(std::string header,std::string date,std::string format,std::string message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add(std::string header,QDateTime date,std::string message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add(std::string header,std::string date,std::string format,std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    log.set_customs(customs);
    this->logs.push_back(log);
}

void LOGS::add(std::string header,QDateTime,std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_message(message);
    log.set_customs(customs);
    this->logs.push_back(log);
}

void LOGS::add_msg(std::string message)
{
    LOG log = LOG(this->header,message,this->customs);
    this->logs.push_back(log);
}

void LOGS::add_msg(std::string message, QDateTime date)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_date(date);
    this->logs.push_back(log);
}

void LOGS::add_msg(std::string message,std::string date,std::string format)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_date(date,format);
    this->logs.push_back(log);
}

void LOGS::add_msg(std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG(this->header,message,customs);
    this->logs.push_back(log);
}

void LOGS::add_msg(std::string message,std::string date,std::string format,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG(this->header,message,customs);
    log.set_date(date,format);
    this->logs.push_back(log);
}

void LOGS::remove(int index)
{
    logs.erase(logs.begin()+index);
}

void LOGS::remove(std::string message, bool all, bool first,bool last)
{
    if(first || all)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_message()==message)
            {
                logs.erase(it);
                if(first)
                    break;
            }
        }
    }
    if(last)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_message()==message)
            {
                logs.erase(it.base());
                    break;
            }
        }
    }
}

void LOGS::remove_by_date(std::string date, std::string format, bool all, bool first,bool last)
{
    if(first || all)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_date(format)==date)
            {
                logs.erase(it);
                if(first)
                    break;
            }
        }
    }
    if(last)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date(format)==date)
            {
                logs.erase(it.base());
                    break;
            }
        }
    }
}

void LOGS::remove_by_date(QDateTime date, bool all, bool first,bool last)
{
    if(first || all)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_date()==date)
            {
                logs.erase(it);
                if(first)
                    break;
            }
        }
    }
    if(last)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date()==date)
            {
                logs.erase(it.base());
                    break;
            }
        }
    }
}

void LOGS::change_message(int index, std::string newMessage)
{
    logs.at(index).set_message(newMessage);
}

LOG* LOGS::get_LOG(int index)
{
    return &logs.at(index);
}

LOG* LOGS::get_LOG(std::string message, bool reverse)
{
    if(!reverse)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_message()==message)
            {
                return it.base();
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_message()==message)
            {
                return it.base().base();
            }
        }
    }
    return nullptr;
}

LOG* LOGS::get_LOG(std::string date,std::string format, bool reverse)
{
    if(!reverse)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_date(format)==date)
            {
                return it.base();
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date(format)==date)
            {
                return it.base().base();
            }
        }
    }
    return nullptr;
}

LOG* LOGS::get_LOG(QDateTime date, bool reverse)
{
    if(!reverse)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_date()==date)
            {
                return it.base();
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date()==date)
            {
                return it.base().base();
            }
        }
    }
    return nullptr;
}

std::vector<LOG> LOGS::get_LOGs()
{
    return this->logs;
}

std::vector<LOG> LOGS::get_LOGs(int indexFrom, int indexTo)
{
    std::vector<LOG> result = std::vector<LOG>(logs.begin()+indexFrom,logs.end()+indexTo);
    return result;
}

std::vector<LOG> LOGS::get_LOGs(std::string message)
{
    std::vector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_message()==message)
        {
            result.push_back(*it);
        }
    }

    return result;
}

std::vector<LOG> LOGS::get_LOGs_by_date(std::string date,std::string format)
{
    std::vector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_date(format)==date)
        {
            result.push_back(*it);
        }
    }

    return result;
}

std::vector<LOG> LOGS::get_LOGs_by_date(QDateTime date)
{
    std::vector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_date()==date)
        {
            result.push_back(*it);
        }
    }

    return result;
}

int LOGS::save(char mode) // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku
{
    QFile file(QString::fromStdString(fileName));
    file.open(QFileDevice::OpenModeFlag::ReadWrite);
    if(!file.isOpen())
    {
        std::cout<<"something_wrong";
        return -1;
    }
    file.write("test",5);
    file.close();
    return 0;
}

void LOGS::autosave_start()
{

}

void LOGS::autosave_start(int autoSaveTime)
{
    this->autoSaveTime=autoSaveTime;
}
