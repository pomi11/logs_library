#include "logs.h"
#include <QFile>

LOGS::LOGS()
{
    this->fs = new XML();
}

void LOGS::add(LOG log)
{
    this->logs.push_back(log);
}

void LOGS::add(QString header,QString date,QString format,QString message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add(QString header,QDateTime date,QString message)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date);
    log.set_date_format(this->format);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add(QString header,QString date,QString format,QString message,QMap<QString,QString> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_date(date,format);
    log.set_message(message);
    log.add_customs(customs);
    this->logs.push_back(log);
}

void LOGS::add(QString header,QDateTime,QString message,QMap<QString,QString> customs)
{
    LOG log = LOG();
    log.set_header(header);
    log.set_message(message);
    log.add_customs(customs);
    this->logs.push_back(log);
}

void LOGS::add_msg(QString message, QString type, QString header, QDateTime date, QString format, QMap<QString,QString> customs)
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
    log.add_customs(customs);
    log.set_message(message);

    logs.push_back(log);
}

void LOGS::remove(int index)
{
    logs.erase(logs.begin()+index);
}

void LOGS::remove(QString message, bool all, bool first,bool last)
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

void LOGS::remove_by_date(QString date, QString format, bool all, bool first,bool last)
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

void LOGS::change_message(int index, QString newMessage)
{
    logs[index].set_message(newMessage);
}

LOG* LOGS::get_LOG(int index)
{
    return &logs[index];
}

LOG* LOGS::get_LOG(QString message, bool reverse)
{
    if(!reverse)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_message()==message)
            {
                return it;
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_message()==message)
            {
                return it.base();
            }
        }
    }
    return nullptr;
}

LOG* LOGS::get_LOG(QString date,QString format, bool reverse)
{
    if(!reverse)
    {
        for(auto it = logs.begin();it<logs.end();it++)
        {
            if(it->get_date(format)==date)
            {
                return it;
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date(format)==date)
            {
                return it.base();
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
                return it;
            }
        }
    }
    if(reverse)
    {
        for(auto it = logs.rbegin();it<logs.rend();it++)
        {
            if(it->get_date()==date)
            {
                return it.base();
            }
        }
    }
    return nullptr;
}

QVector<LOG> LOGS::get_LOGs()
{
    return this->logs;
}

QVector<LOG> LOGS::get_LOGs(int indexFrom, int indexTo)
{
    QVector<LOG> result = QVector<LOG>(logs.begin()+indexFrom,logs.end()+indexTo);
    return result;
}

QVector<LOG> LOGS::get_LOGs(QString message)
{
    QVector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_message()==message)
        {
            result.push_back(*it);
        }
    }

    return result;
}

QVector<LOG> LOGS::get_LOGs_by_date(QString date,QString format)
{
    QVector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_date(format)==date)
        {
            result.push_back(*it);
        }
    }

    return result;
}

QVector<LOG> LOGS::get_LOGs_by_date(QDateTime date)
{
    QVector<LOG> result;
    for(auto it = logs.begin();it<logs.end();it++)
    {
        if(it->get_date()==date)
        {
            result.push_back(*it);
        }
    }

    return result;
}

int LOGS::save(QString filePath, char mode, FILE_STRUCT *fileStruct) // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku
{
    //T toSave = T(fileName,mainHeader,footer,logs);
   /* if(fileStruct==nullptr)
    {
        std::cout<<"Brak struktury pliku. Uzyty zostanie domyslny";
    }
    else*/
    if(fileStruct!=nullptr)
        this->fs = fileStruct;

    QFile file(filePath);
    file.open(QFile::WriteOnly|QFile::Text);
    file.write(fs->start_file("").c_str());
    QVector<QMap<QString,QString>> map;
    for(auto it = this->logs.begin();it!=this->logs.end();it++)
    {
        map.push_back(it->get_val_map());
    }
    file.write(fs->sys_info(SYS_INFO().get_info_map()).c_str());
    file.write(fs->log(map).c_str());
    file.write(fs->end_file().c_str());
    file.close();
    return 0;
}

void LOGS::autosave(QString filePath, char mode, FILE_STRUCT *fileStruct)
{
    while(!stop)
    {
        save(filePath,mode,fileStruct);
        QThread::sleep(autoSaveTime);
    }
}

void LOGS::autosave_start(QString filePath, char mode,FILE_STRUCT *fileStruct)
{
    auto func1 = std::bind(&LOGS::autosave,this,filePath,mode,fileStruct);
    QtConcurrent::run(func1);
}

void LOGS::autosave_stop()
{
    this->stop=true;
   // this->thread->
}

void LOGS::autosave_start(int autoSaveTime,QString filePath, char mode,FILE_STRUCT *fileStruct)
{
    this->autoSaveTime=autoSaveTime;
    autosave_start(filePath,mode);
}

QDataStream& operator>>(QDataStream& in,LOGS & fs)
{
    QString fileName,path,mainHeader,format,footer,type;
    QVector<LOG> logs;
    //int autoSaveTime;

    in>>fileName;
    in>>path;
    in>>mainHeader;
    in>>format;
    in>>footer;
    in>>type;
    in>>logs;
    fs = LOGS(logs);
    fs.set_file_name(fileName);
    fs.set_file_path(path);
    fs.set_main_header(mainHeader);
    fs.set_date_format(format);
    fs.set_footer(footer);
    fs.set_default_type(type);
    return in;
}

QDataStream& operator<<(QDataStream& out,LOGS &fs)
{
    out<<fs.get_file_name();
    out<<fs.get_file_path();
    out<<fs.get_main_header();
    out<<fs.get_date_format();
    out<<fs.get_footer();
    out<<fs.get_default_type();
    out<<fs.get_LOGs(0);

    return out;
}

