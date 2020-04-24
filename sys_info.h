#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "logs_library_global.h"
#include <iostream>
#include <vector>
#include <cpuid.h>
#include <QSysInfo>
#include <QString>
#include <QStorageInfo>
#include <QMap>
#include <memory>
#include <QDataStream>

#ifdef __WIN32
    #include <sysinfoapi.h>
    #include <windef.h>
    #include <winbase.h>
    #include <psapi.h>
#endif

#ifdef __linux__
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <sys/sysinfo.h>
    #include <stdio.h>
    #include <unistd.h>
#endif

struct LOGS_LIBRARY_EXPORT DISK_INFO
{
    QString name;
    int number;
    qint64 totalSpace;
    qint64 usageSpace;
    qint64 freeSpace;
};

/*struct INFO
{
    QString description, short_descr,value;

};*/

class LOGS_LIBRARY_EXPORT SYS_INFO
{
private:
    QMap<QString,bool> enabledInfos;
    QMap<QString,QString> infos;
    QString sysname,CPUname,arch,username;
    int cores;
    unsigned long long int maxMemory,availMemory,useMemory,procPeak,procCurr;
    QVector<DISK_INFO> disks;
public:
    SYS_INFO();
    SYS_INFO(QMap<QString,bool> enabledInfos,QMap<QString,QString> infos,
             QString sysname,QString CPUname,QString arch, QString username,int cores,
             quint64 maxMemory, quint64 availMemory, quint64 useMemory,quint64 procPeak,
             quint64 procCurr, QVector<DISK_INFO> disks);

    QString get_sysname() const {return sysname;};
    QString get_cpuname() const {return CPUname;};
    QString get_arch() const {return arch;};
    QString get_username() const {return username;};

    int get_cores() const {return cores;};

    QMap<QString,bool> get_enabled_infos() {return enabledInfos;};

    unsigned long long int get_max_memory() const {return maxMemory;} ;
    unsigned long long int get_avail_memory() const {return availMemory;};
    unsigned long long int get_use_memory() const {return useMemory;};
    unsigned long long int get_proc_peak() const {return procPeak;};
    unsigned long long int get_proc_curr() const {return procCurr;};

    QVector<DISK_INFO> get_disks_info() const {return disks;};

    int gather_sysname();
    int gather_CPUname();
    int gather_arch();
    int gather_username();
    int gather_cores();
    int gather_max_memory();
    int gather_avail_memory();
    int gather_use_memory();
    int gather_proc_peak();
    int gather_proc_curr();
    int gather_disks_info();
    int gather_info();

//    QString gather_get(QString infoName);
//    QVector<std::pair<QString,QString>> gather_get(QVector<QString> infoNames);
    QString get_info(QString infoName);

    QVector<QString> get_info(QVector<QString> infoNames = QVector<QString>());

    QMap<QString,QString> get_info_map();
    QMap<QString,QString> get_info_map(QVector<QString> infoNames);

    void disable_all();

    int set_enabled(QString infoname, bool enable=true);
    int set_enabled(QVector<QString> infoNames= QVector<QString>(),bool enable=true);
    static QVector<QString> listInfo();
};

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,SYS_INFO &fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,SYS_INFO fs);

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,DISK_INFO &fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,DISK_INFO const &fs);

/*LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,QVector<DISK_INFO> &list);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,QVector<DISK_INFO> const &list);*/


#endif // SYSTEM_INFO_H
