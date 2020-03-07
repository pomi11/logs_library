#ifndef LOGS_H
#define LOGS_H

#include "logs_library.h"

template <class T> class LOGS
{
private:
    std::string login, fileName,path,mainHeader,header,format,footer,type;
    std::vector<LOG> logs;
    std::vector<std::pair<std::string,std::string>> customs;
    std::pair<std::string,std::string> braces;
    int autoSaveTime = 0;
public:
    LOGS();
    LOGS(std::string fileName) {this->fileName = fileName;};
    LOGS(std::string fileName,std::string path) {this->fileName=fileName;this->path=path;};
    LOGS(std::vector<LOG> logs) {this->logs = logs;};
    LOGS(std::string fileName,std::vector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(std::string header,std::string date,std::string format,std::string message);
    void add(std::string header,QDateTime date,std::string message);
    void add(std::string header,std::string date,std::string format,std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add(std::string header,QDateTime,std::string message,std::vector<std::pair<std::string,std::string>> customs);

    /*void add_msg(std::string message);
    void add_msg(std::string message,std::string type);

    void add_msg(std::string message,QDateTime date);
    void add_msg(std::string message,std::string date,std::string format);

    void add_msg(std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message,std::string date,std::string format,std::vector<std::pair<std::string,std::string>> customs);*/

    //void add_msg(std::string message,std::string type="", std::string header = "", std::string date="",std::string format="",std::vector<std::pair<std::string,std::string>> customs={});
    void add_msg(std::string message,std::string type="", std::string header = "", QDateTime date=QDateTime(),std::string format="",std::vector<std::pair<std::string,std::string>> customs={});

    void remove(int index);
    void remove(std::string message, bool all=true, bool first=false,bool last=false);
    void remove_by_date(std::string date, std::string format, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QDateTime date, bool all=true, bool first=false,bool last=false);

    //void replace(LOG log, LOG log2);

    void change_message(int index, std::string newMessage);

    LOG* get_LOG(int index);
    LOG* get_LOG(std::string message, bool reverse=false);
    LOG* get_LOG(std::string date,std::string format, bool reverse=false);
    LOG* get_LOG(QDateTime date, bool reverse=false);

    std::vector<LOG> get_LOGs();
    std::vector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);
    std::vector<LOG> get_LOGs(std::string message);
    std::vector<LOG> get_LOGs_by_date(std::string date,std::string format);
    std::vector<LOG> get_LOGs_by_date(QDateTime date);
    // std::vector<LOG> get_LOGs_by_date();

    void set_file_name(std::string fileName) {this->fileName=fileName;};
    void set_file_path(std::string path) {this->path=path;};

    void set_date_format(std::string format) {this->format=format;};
    void set_main_header(std::string header) {this->mainHeader=header;};
    void set_footer(std::string footer) {this->footer=footer;};
    void set_default_type(std::string type) {this->type=type;};

    int save(char mode='r'); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave_start();
    void autosave_start(int autoSaveTime);
    void set_autosave_time(int time) {this->autoSaveTime=time;};
    void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
    void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};
};

#endif // LOGS_H



template <class T> LOGS<T>::LOGS()
{

}

template<class T> void LOGS<T>::add(LOG log)
{
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add(std::string header,std::string date,std::string format,std::string message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add(std::string header,QDateTime date,std::string message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date);
    log.set_date_format(this->format);
    log.set_message(message);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add(std::string header,std::string date,std::string format,std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    log.set_customs(customs);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add(std::string header,QDateTime,std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_message(message);
    log.set_customs(customs);
    this->logs.push_back(log);
}
/*
template<class T> void LOGS<T>::add_msg(std::string message)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_type(this->type);
    log.set_date_format(this->format);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add_msg(std::string message,std::string type)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_type(type);
    log.set_date_format(this->format);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add_msg(std::string message, QDateTime date)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_date(date);
    log.set_date_format(this->format);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add_msg(std::string message,std::string date,std::string format)
{
    LOG log = LOG(this->header,message,this->customs);
    log.set_date(date,format);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add_msg(std::string message,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG(this->header,message,customs);
    log.set_date_format(this->format);
    this->logs.push_back(log);
}

template<class T> void LOGS<T>::add_msg(std::string message,std::string date,std::string format,std::vector<std::pair<std::string,std::string>> customs)
{
    LOG log = LOG(this->header,message,customs);
    log.set_date(date,format);
    this->logs.push_back(log);
}*/

/*template<class T> void LOGS<T>::add_msg(std::string message, std::string type, std::string header, std::string date, std::string format, std::vector<std::pair<std::string, std::string> > customs)
{
    if(type=="")
        type = this->type;

    if(header=="")
        header = this->header;

    if(date=="")
    {
        if(format=="")
            date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString();
        else
            date = QDateTime::currentDateTime().toString(QString::fromStdString(format)).toStdString();
    }

    if(customs.size()==0)
        this->customs=customs;

    LOG log = LOG();
    log.set_type(type);
    log.set_header(header);
    log.set_date(date,format);
    log.set_customs(customs);
    log.set_message(message);

    logs.push_back(log);
}
*/
template<class T> void LOGS<T>::add_msg(std::string message, std::string type, std::string header, QDateTime date, std::string format, std::vector<std::pair<std::string, std::string> > customs)
{
    if(type=="")
        type = this->type;

    if(header=="")
        header = this->header;

    if(date==QDateTime())
    {
            date = QDateTime::currentDateTime();
    }

    if(format=="")
        format=this->format;

    if(customs.size()==0)
        customs=this->customs;

    LOG log = LOG();
    log.set_date_format(format);
    log.set_type(type);
    log.set_header(header);
    log.set_date(date);
    log.set_customs(customs);
    log.set_message(message);

    logs.push_back(log);
}

template<class T> void LOGS<T>::remove(int index)
{
    logs.erase(logs.begin()+index);
}

template<class T> void LOGS<T>::remove(std::string message, bool all, bool first,bool last)
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

template<class T> void LOGS<T>::remove_by_date(std::string date, std::string format, bool all, bool first,bool last)
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

template<class T> void LOGS<T>::remove_by_date(QDateTime date, bool all, bool first,bool last)
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

template<class T> void LOGS<T>::change_message(int index, std::string newMessage)
{
    logs.at(index).set_message(newMessage);
}

template<class T> LOG* LOGS<T>::get_LOG(int index)
{
    return &logs.at(index);
}

template<class T> LOG* LOGS<T>::get_LOG(std::string message, bool reverse)
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

template<class T> LOG* LOGS<T>::get_LOG(std::string date,std::string format, bool reverse)
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

template<class T> LOG* LOGS<T>::get_LOG(QDateTime date, bool reverse)
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

template<class T> std::vector<LOG> LOGS<T>::get_LOGs()
{
    return this->logs;
}

template<class T> std::vector<LOG> LOGS<T>::get_LOGs(int indexFrom, int indexTo)
{
    std::vector<LOG> result = std::vector<LOG>(logs.begin()+indexFrom,logs.end()+indexTo);
    return result;
}

template<class T> std::vector<LOG> LOGS<T>::get_LOGs(std::string message)
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

template<class T> std::vector<LOG> LOGS<T>::get_LOGs_by_date(std::string date,std::string format)
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

template<class T> std::vector<LOG> LOGS<T>::get_LOGs_by_date(QDateTime date)
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

template<class T> int LOGS<T>::save(char mode) // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku
{
    T toSave = T(fileName,mainHeader,footer,logs);
    toSave.set_braces(braces);
    toSave.write();
    return 0;
}

template<class T> void LOGS<T>::autosave_start()
{

}

template<class T> void LOGS<T>::autosave_start(int autoSaveTime)
{
    this->autoSaveTime=autoSaveTime;
}
