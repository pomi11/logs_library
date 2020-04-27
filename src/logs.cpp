#include "include/logs.h"
#include <QFile>

LOGS::LOGS()
{
    this->ic = nullptr;
    autoSaveTime = 10;
    autoLogTime = 10;
    threadNum = 0;

    autosaving = false;
    autologging =false;
    showSystemMemAvail = false;
    showSystemMemUsage = false;
    showProcMemUsage = false;
    showProcMemMax = false;
    showSysSummary = true;
    showLogNumber = true;
    showLogType = true;
    showLogDate = true;
    showLogHeader = false;
    isCustomLogSI = false;

    isConnected=-1;
    cfg = nullptr;

    d = new LOG();

    this->fs = new XML();
    this->si = new SYS_INFO();

    this->set_date_format("dd/MM/yyyy hh:mm:ss");
    autologMessage=nullptr;
    LOG c;
    c.set_message("System summarry");
    c.set_type("SYSTEM_INFO");
    si->set_enabled();
    c.add_sys_info(*si);
    logs.push_back(c);


    d->set_type("INFO");
    d->set_date_format(format);
}

void LOGS::add(LOG log)
{
    this->logs.push_back(log);
}

void LOGS::add(QString header,QString date,QString format,QString message)
{
    if(header=="")
        header = this->header;

    if(format=="")
        format=this->format;

    LOG log = *d;
    log.set_date_format(format);
    log.set_type(type);
    log.set_header(header);
    log.set_date(QDateTime::fromString(date,format));
    //log.add_customs(customs);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add(QString header,QDateTime date,QString message)
{
    if(header=="")
        header = this->header;

    if(date==QDateTime())
    {
            date = QDateTime::currentDateTime();
    }

    LOG log = *d;
    log.set_header(header);
    log.set_date(date);
    //log.add_customs(customs);
    log.set_message(message);
    this->logs.push_back(log);
}

void LOGS::add_msg(QString message)
{
    if(this->showProcMemMax || this->showProcMemUsage || this->showSystemMemAvail || this->showSystemMemUsage)
    {
        SYS_INFO s;// = *si;
        s.disable_all();
        s.gather_info();
        s.set_enabled("proc_peak",showProcMemMax);
        s.set_enabled("proc_curr",showProcMemUsage);
        s.set_enabled("avail_memory",showSystemMemAvail);
        s.set_enabled("use_memory",showSystemMemUsage);
        d->add_sys_info(s);

    }

    LOG log = *d;
    log.set_date(QDateTime::currentDateTime());
    log.set_message(message);

    logs.push_back(log);
}

void LOGS::add_msg(QString message, QString type)
{
    if(isCustomLogSI)
    {
        d->get_sys_info()->gather_info();
    }
    else
    if(this->showProcMemMax || this->showProcMemUsage || this->showSystemMemAvail || this->showSystemMemUsage)
    {
        SYS_INFO s;// = *si;
        s.disable_all();
        s.gather_info();
        s.set_enabled("proc_peak",showProcMemMax);
        s.set_enabled("proc_curr",showProcMemUsage);
        s.set_enabled("avail_memory",showSystemMemAvail);
        s.set_enabled("use_memory",showSystemMemUsage);
        d->add_sys_info(s);

    }

    LOG log = *d;
    //log.add_customs(customs);
    log.set_type(type);
    log.set_date(QDateTime::currentDateTime());
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

int LOGS::save()
{
    if(isConnected==0)
    {
        QVector<LOG> logs = this->get_LOGs(0);
        int w = ic->send_data(logs);
        return w;
    }

    QString filePath;
    if(this->path!="")
        filePath+=path;

    if(fileName=="")
        fileName=QDir::toNativeSeparators(QDir::homePath()+"/log.xml");
    filePath+=fileName;
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly|QFile::Text))
        return 1;
    file.write(fs->start_file("").c_str());
    QVector<QMap<QString,QMap<QString,QString>>> map;

    for(auto it = this->logs.begin();it!=this->logs.end();it++)
    {
        //it->add_sys_info(*this->si);
        QMap<QString,QMap<QString,QString>> tmp;
        tmp["basic"]=it->get_basic();
        tmp["SYS_INFO"]=it->get_sys_info_map();
        map.push_back(tmp);
    }
   // file.write(fs->sys_info(si->get_info_map()).c_str());
    file.write(fs->log(map).c_str());
    file.write(fs->end_file().c_str());
    file.close();
    return 0;
}

int LOGS::save(QString filePath, FILE_STRUCT *file_struct)
{
    this->path="";
    this->fileName=filePath;
    if(file_struct!=nullptr)
        this->fs = file_struct;
    return save();
}

int LOGS::save(FILE_STRUCT *file_struct)
{
    this->fs = file_struct;
    return save();
}

void LOGS::autosave(QString filePath, FILE_STRUCT *fileStruct)
{
    if(filePath=="")
    {
        if(fileStruct!=nullptr)
        {
            while(autosaving)
            {
                save(fileStruct);
                QThread::sleep(autoSaveTime);
            }
        }
        else
        {
            while(autosaving)
            {
                save();
                QThread::sleep(autoSaveTime);
            }
        }
    }
    if(filePath!="")
    {
        while(autosaving)
        {
            save(filePath,fileStruct);
            QThread::sleep(autoSaveTime);
        }
    }
}

int LOGS::autolog()
{
    while(autologging)
    {
        LOG l;
        if(cfg==nullptr)
        {
            l = *d;
            if(this->showProcMemMax || this->showProcMemUsage || this->showSystemMemAvail || this->showSystemMemUsage)
            {
              //  this->si->gather_info();
                SYS_INFO s;// = *si;
                s.disable_all();
                s.gather_info();
                s.set_enabled("proc_peak",showProcMemMax);
                s.set_enabled("proc_curr",showProcMemUsage);
                s.set_enabled("avail_memory",showSystemMemAvail);
                s.set_enabled("use_memory",showSystemMemUsage);
                l.add_sys_info(s);

            }
        }
        else
            l = *cfg;
        qDebug()<<"running";
        l.get_sys_info()->gather_info();
        l.set_date(QDateTime::currentDateTime());

        if(autologMessage==nullptr)
        {
            if(l.get_message()=="")
            {
                l.set_message("This is automatic log");
            }
        }
        else
        {
            l.set_message(*autologMessage);
        }
        logs.push_back(l);
        QThread::sleep(autoLogTime);
    }
    return 0;
}

int LOGS::autolog_start(int autoLogTime)
{
    this->autoLogTime=autoLogTime;
    if(!futureLog1.isRunning())
    {
        autologging=true;
        auto func1 = std::bind(&LOGS::autolog,this);
        futureLog1 = QtConcurrent::run(func1);
        qDebug()<<"Autolog started successfully";
        return 0;
    }
    {
        qDebug()<<"Autolog is running already!";
        return -1;
    }
}

int LOGS::autolog_start(LOG *cfg, SYS_INFO *si)
{
    *this->cfg = *cfg;
    this->cfg->add_sys_info(*si);
    if(!futureLog1.isRunning())
    {
        autologging=true;
        return autolog_start(this->autoLogTime);
    }
    {
        qDebug()<<"Autolog is running already!";
        return -1;
    }
}

int LOGS::autosave_start()
{
    if(!futureSave1.isRunning())
    {
        autosaving=true;
        auto func1 = std::bind(&LOGS::autosave,this,"",nullptr);
        futureSave1 = QtConcurrent::run(func1);
        qDebug()<<"Autosave started successfully";
        return 0;
    }
    {
        qDebug()<<"Autosave is running already!";
        return -1;
    }
}

int LOGS::autosave_start(FILE_STRUCT* fs)
{
    if(!futureSave1.isRunning())
    {
        autosaving=true;
        auto func1 = std::bind(&LOGS::autosave,this,QString(""),fs);
        futureSave1 = QtConcurrent::run(func1);
        qDebug()<<"Autosave started successfully";
        return 0;
    }
    {
        qDebug()<<"Autosave is running already!";
        return -1;
    }
}

int LOGS::autosave_start(int autoSaveTime)
{
    if(!futureSave1.isRunning())
    {
        autosaving=true;
        this->autoSaveTime=autoSaveTime;
        return autosave_start();
    }
    {
        qDebug()<<"Autosave is running already!";
        return -1;
    }
}

int LOGS::autosave_start(QString filePath, FILE_STRUCT *fileStruct)
{
    if(!futureSave1.isRunning())
    {
        autosaving=true;
        auto func1 = std::bind(&LOGS::autosave,this,filePath,fileStruct);
        futureSave1 = QtConcurrent::run(func1);
        qDebug()<<"Autosave started successfully";
        return 0;
    }
    {
        qDebug()<<"Autosave is running already!";
        return -1;
    }
}

int LOGS::autosave_start(int autoSaveTime,QString filePath, FILE_STRUCT *fileStruct)
{
    if(!futureSave1.isRunning())
    {
        autosaving=true;
        this->autoSaveTime=autoSaveTime;
        return autosave_start(filePath,fileStruct);
    }
    {
        qDebug()<<"Autosave is running already!";
        return -1;
    }
}

void LOGS::autosave_stop()
{
    qDebug()<<"stopping autosave";
    this->autosaving=false;
    futureSave1.cancel();
    while(futureSave1.isRunning());
    qDebug()<<"stoped autosave";
}

void LOGS::autolog_stop()
{
    qDebug()<<"stopping autolog";
    this->autologging=false;
    futureLog1.cancel();
    while(futureLog1.isRunning());
    qDebug()<<"stoped autolog";
}



int LOGS::connect_to_log_serv(QString host, quint16 port, QString username, QString password)
{
    ic = new DirectConnection(host,port,username,password);
    isConnected = ic->connect();
    return isConnected;
}

void LOGS::set_default_header(QString header)
{
    if(header!="")
    {
        this->fs->show_log_header(true);
        this->header=header;
        this->d->set_header(header);
    }
}

void LOGS::stop_watch(QString name)
{
    Watcher * dd = nullptr;

    if(watches.count()>0)
        dd = watches[name];

    if(dd!=nullptr)
        watches[name]->stopWatch();

    while(watches[name]->is_running());
    delete dd;
    dd = nullptr;
    watches[name] = nullptr;
    qDebug()<<"stop watching";
}
