#ifndef LOGS_H
#define LOGS_H

#include "logs_library_global.h"
#include "watcher.h"
#include "file_struct.h"
#include "sys_info.h"
#include <thread>
#include <mutex>
#include <QtConcurrent/QtConcurrent>
#include "iconnector.h"


class LOGS_LIBRARY_EXPORT LOGS : public QObject
{
    Q_OBJECT
private:
    QString login, fileName,path,header,format,footer,type, *autologMessage=nullptr;
    //QString mainHeader;
    QVector<LOG> logs;
    QMap<QString,QString> customs;
    //std::pair<QString,QString> braces;
    int autoSaveTime = 10, autoLogTime = 10,
        threadNum = 0;
    FILE_STRUCT* fs; // do ogarnięcia temat wycieku pamięci ewentualny
    SYS_INFO *si;
   // std::thread *thread;
    bool autosaving = false, autologging =false, showSystemMemAvail = false,showSystemMemUsage = false, showProcMemUsage = false, showProcMemMax = false,
         showSysSummary = true, showLogNumber = true, showLogType = true, showLogDate = true, showLogHeader = false, isCustomLogSI = false;
    QVector<int> runningThreads;
    int  isConnected=-1;
    LOG *d, *cfg = nullptr;
    IConnector *ic;
    //QFutureWatcher<void> *futureSave=nullptr, *futureLog=nullptr;
    QFuture<void> futureSave1, futureLog1;
    QMap<QString,Watcher*> watches;
    QMap<QString,QString> watchesValues;
    bool lock = false;
    std::mutex mtx;
public:
    LOGS();
    LOGS(QString fileName) {this->fileName = fileName;};
    LOGS(QString fileName,QString path) {this->fileName=fileName;this->path=path;};
    LOGS(QVector<LOG> logs) {this->logs = logs;};
    LOGS(QString fileName,QVector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(QString header,QString date,QString format,QString message);
    void add(QString header,QDateTime date,QString message);

    void add_msg(QString message);
    void add_msg(QString message,QString type);

    template<template<typename> class C> void add(C<LOG> log);
    //template<typename C> void add(C *log);

    void show_sys_summary(bool val) {showSysSummary=val; this->fs->show_sys_summary(val);};
    void show_file_date(bool val) {this->fs->show_file_date(val);};

    void show_log_number(bool val) {showLogNumber=val;this->fs->show_log_number(val);};
    void show_log_type(bool val) {showLogType=val;this->fs->show_log_type(val);};
    void show_log_date(bool val) {showLogDate=val;this->fs->show_log_date(val);};
    void show_log_header(bool val) {showLogHeader=val;this->fs->show_log_header(val);};

    void show_log_memory_avail(bool val){showSystemMemAvail=val;};
    void show_log_memory_usage(bool val){showSystemMemUsage=val;};
    void show_log_proc_memory_usage(bool val){showProcMemUsage=val;};
    void show_log_proc_memory_max(bool val){showProcMemMax=val;};

    void remove(int index);
    void remove(QString message, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QString date, QString format, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QDateTime date, bool all=true, bool first=false,bool last=false);

    //void replace(LOG log, LOG log2);

    void change_message(int index, QString newMessage);

    LOG* get_LOG(int index);
    LOG* get_LOG(QString message, bool reverse=false);
    LOG* get_LOG(QString date,QString format, bool reverse=false);
    LOG* get_LOG(QDateTime date, bool reverse=false);

    QVector<LOG> get_LOGs();
    QVector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);
    QVector<LOG> get_LOGs(QString message);
    QVector<LOG> get_LOGs_by_date(QString date,QString format);
    QVector<LOG> get_LOGs_by_date(QDateTime date);
    // QVector<LOG> get_LOGs_by_date();

    QString get_file_name() {return fileName;};
    QString get_file_path() {return path;};
    //QString get_main_header() {return mainHeader;};
    QString get_date_format() {return format;};
   // QString get_footer()    {return footer;};
    QString get_default_type() {return type;};
    FILE_STRUCT *get_file_struct() {return fs;};

    void set_file_name(QString fileName) {this->fileName=fileName;};
    void set_file_path(QString path) {this->path=path;};

    void set_date_format(QString format) {this->format=format;this->d->set_date_format(format);};
    void set_default_header(QString header);
    void set_custom_log_sys_info(SYS_INFO si) {this->d->add_sys_info(si);isCustomLogSI=true;};
    void set_default_type(QString type) {this->type=type;this->d->set_type(type);};

    int save();
    int save(FILE_STRUCT *file_struct);
    int save(QString filePath, FILE_STRUCT *file_struct = nullptr); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave(QString filePath, FILE_STRUCT *file_struct = nullptr);
    //void autosave();

    int autosave_start();
    int autosave_start(int autoSaveTime);
    int autosave_start(FILE_STRUCT *file_struct);
    int autosave_start(int autoSaveTime,QString filePath, FILE_STRUCT *file_struct = nullptr);
    int autosave_start(QString filePath, FILE_STRUCT *file_struct = nullptr);

    int autolog();
    int autolog_start(int autoSaveTime= 10);
    int autolog_start(LOG *cfg, SYS_INFO *si = nullptr);

    void set_autolog_message(QString *m){autologMessage = m;};


    void autosave_stop();
    void autolog_stop();

    void set_autosave_time(int time) {this->autoSaveTime=time;};
    void set_autolog_time(int time) {this->autoLogTime=time;};

    void set_connection(IConnector *conn) {this->ic = conn;isConnected=ic->is_connected();};
    int connect_to_log_serv(QString host,quint16 port,QString username="",QString password="");

    void stop_watch(QString &name);

    template<typename T> void watch(QString &name, T *val/*,RealWatcher<T> *rw*/);
    template<typename T> void watching2(T *val, QString name/*,RealWatcher<T> *rw*/,Watcher *w);
    template<typename T> void save_watching(T val, QString result);
    template<typename T> void watching(RealWatcher<T> *rw, QString *result);

    template<typename T> QString decode_type(T *val, int &errorcode);
    //int connect_to_ftp(QString host,quint16 port,QString username="",QString password=""); -- do zrobienia
    //int connect_to_ssh(QString host,quint16 port,QString username="",QString password=""); -- do zrobienia


    //void set_braces(QString start,QString end) {this->braces=std::make_pair(start,end);};
    //void set_braces(std::pair<QString,QString> braces) {this->braces=braces;};
};

template<template<typename> class C> void LOGS::add(C<LOG> log)
{
    for(auto it = log.begin();it!=log.end();it++)
    {
        this->logs.push_back(*it);
    }
}

template<typename T> void LOGS::watch(QString &name, T *val/*,RealWatcher<T> *rw*/)
{

    Watcher *tmp = new Watcher();
    this->watches[name]=tmp;
    int res = 0;
    QString helper = watchesValues[name] = decode_type(val,res);
   // rw->set_watched(true);
    this->add_msg("starting watching value "+name+" = "+helper);
  //  tmp->set_first_thread(new std::thread(&Watcher::watch<T>,tmp,val,rw));
  //  tmp->set_second_thread(new std::thread(&LOGS::watching<T>,this,rw,&this->watchesValues[name]));

    //poniżej nowa wersja

    std::thread *tx=new std::thread(&LOGS::watching2<T>,this,val,name/*,rw*/,tmp);
    tmp->set_second_thread(tx);

    //tmp->watch(val,rw);
    QThread::sleep(2);
    qDebug()<<"Watching started";
};

template<typename T> void LOGS::watching2(T *val, QString name,/*RealWatcher<T> *rw,*/Watcher *w)
{
    int myNum = this->threadNum++;
    runningThreads.push_back(myNum);
    LOG tmp = *d;
    QVector<LOG> threadLogs;
    T lastVal = *val;

    while(w->is_running())
    {
        int t=*val;
//        qDebug()<<"tttt"<<t;
//        qDebug()<<"xxxx"<<lastVal;
        if(t!=lastVal)
        {
           // *tmp = *currval;
            //rw->set_val(*val);
            int c =1;
            lastVal = t;
            this->watchesValues[name]=decode_type(&lastVal,c);
            tmp.set_message("value changed :"+name+" on "+watchesValues[name]);
            tmp.set_date(QDateTime::currentDateTime());
            threadLogs.push_back(tmp);

            if(mtx.try_lock())
            {
                //this->add_msg("changed value");
                this->add(threadLogs);
                mtx.unlock();
                threadLogs.clear();
            }


            //std::thread *sxce=new std::thread(&LOGS::save_watching<T>,this,lastVal,name);
           // qDebug()<<lastVal;
        }
    }
  //  while(runningThreads[0]!=myNum) {};
  //  this->add(threadLogs);
  //  runningThreads.removeAt(0);
};

template<typename T> void LOGS::save_watching(T val, QString result)
{
    this->add_msg("changed value");
}

    //powyżej watching nowy
    //poniżej watching oryginalny

template<typename T> void LOGS::watching(RealWatcher<T> *rw, QString *result)
    {
    T tmp = rw->get_value();
    while(rw->is_watched())
    {
        T x = rw->get_value();
        if(x!=tmp)
        {
            tmp = x;
           // QString c = "as";//QString::number(tmp);
            int cxce = 1;
            *result = decode_type(&x,cxce);
            //qDebug()<<x;
            this->add_msg("value changed!"+(*result));
            //std::cout<<rw->get_value()<<"\n";
        }
    }
};

template<typename T> QString LOGS::decode_type(T *val, int &errorcode)
{
    if(std::is_convertible<T,int>())
    {
        errorcode=0;
        //int d = static_cast<T>(val);
        int *ds = reinterpret_cast<int*>(val);
        QString res = QString::number(*ds);
        return res;
    }
/*
    if(std::cout<<std::is_convertible<T,QString>())
    {
        errorcode=0;
        return QString(val);
    }

    if(std::cout<<std::is_convertible<T,std::string>())
    {
        errorcode=0;
        return QString::fromStdString(val);
    }

    if(std::cout<<std::is_convertible<T,char*>())
    {
        errorcode=0;
        char *plik = "asd";
        std::string as = std::string(plik);
        return QString::fromStdString(as);
    }*/

    errorcode=-1;
    return "Cannot conver variable!";
}


/*
template<typename C> void LOGS::add(C *log)
{
    qDebug()<<*log;
}*/


LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,LOGS &fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,LOGS &fs);

#endif // LOGS_H
