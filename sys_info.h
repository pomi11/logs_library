#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "logs_library_global.h"
#include <iostream>
#include <vector>
#include <cpuid.h>
#include <QSysInfo>
#include <QString>
#include <QStorageInfo>
#include <memory>

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
    std::string name;
    int number;
    qint64 totalSpace;
    qint64 usageSpace;
    qint64 freeSpace;
};

/*struct INFO
{
    std::string description, short_descr,value;

};*/

class LOGS_LIBRARY_EXPORT SYS_INFO
{
private:
    std::map<std::string,bool> enabledInfos;
    std::map<std::string,std::string> infos;
    std::string sysname,CPUname,arch,username;
    int cores;
    unsigned long long int maxMemory,availMemory,useMemory,procPeak,procCurr;
    std::vector<DISK_INFO> disks;
public:
    SYS_INFO();

    std::string get_sysname() const {return sysname;};
    std::string get_cpuname() const {return CPUname;};
    std::string get_arch() const {return arch;};
    std::string get_username() const {return username;};

    int get_cores() const {return cores;};

    unsigned long long int get_max_memory() const {return maxMemory;} ;
    unsigned long long int get_avail_memory() const {return availMemory;};
    unsigned long long int get_use_memory() const {return useMemory;};
    unsigned long long int get_proc_peak() const {return procPeak;};
    unsigned long long int get_proc_curr() const {return procCurr;};

    std::vector<DISK_INFO> get_disks_info() const {return disks;};

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

//    std::string gather_get(std::string infoName);
//    std::vector<std::pair<std::string,std::string>> gather_get(std::vector<std::string> infoNames);
    std::string get_info(std::string infoName);
    std::vector<std::string> get_info(std::vector<std::string> infoNames = std::vector<std::string>());
    std::map<QString,QString> get_info_map(std::vector<std::string> infoNames = std::vector<std::string>());
    int set_enabled(std::string infoname, bool enable=true);
    int set_enabled(std::vector<std::string> infoNames= std::vector<std::string>(),bool enable=true);
    static std::vector<std::string> listInfo();
};



#endif // SYSTEM_INFO_H
