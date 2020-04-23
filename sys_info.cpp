#include "sys_info.h"

SYS_INFO::SYS_INFO()
{
    enabledInfos["sysname"]=true;
    enabledInfos["arch"]=true;
    enabledInfos["cpuname"]=true;
    enabledInfos["cores"]=true;
    enabledInfos["username"]=true;
    enabledInfos["max_memory"]=true;
    enabledInfos["avail_memory"]=true;
    enabledInfos["use_memory"]=true;
    enabledInfos["proc_peak"]=true;
    enabledInfos["proc_curr"]=true;
    enabledInfos["disks"]=true;

    gather_info();

    infos["sysname"]=this->sysname;
    infos["arch"]=this->arch;
    infos["cpuname"]=this->CPUname;
    infos["cores"]=QString::number(this->cores);
    infos["username"]=this->username;
    infos["max_memory"]=QString::number(this->maxMemory);
    infos["avail_memory"]=QString::number(this->availMemory);
    infos["use_memory"]=QString::number(this->useMemory);
    infos["proc_peak"]=QString::number(this->procPeak);
    infos["proc_curr"]=QString::number(this->procCurr);
    QString tmp,tmp2;
    for(auto it = disks.begin();it!=disks.end();it++)
    {
        tmp2 = (*it).name;
        //tmp2.erase(tmp2.length()-1);
        tmp2 = tmp2.left(tmp2.count()-1);
        infos["disks"]+=tmp2;
        if(it!=disks.end()-1)
        {
            infos["disks"]+="|";
        }
        tmp = "max_";

        infos[tmp+tmp2] = QString::number((*it).totalSpace);
        tmp = "avail_";
        infos[tmp+tmp2] = QString::number((*it).freeSpace);
    }
}

SYS_INFO::SYS_INFO(QMap<QString,bool> enabledInfos,QMap<QString,QString> infos,
                   QString sysname,QString CPUname,QString arch, QString username,int cores,
                   quint64 maxMemory, quint64 availMemory, quint64 useMemory,quint64 procPeak,
                   quint64 procCurr, QVector<DISK_INFO> disks)
{
    this->enabledInfos=enabledInfos;
    this->infos=infos;
    this->sysname=sysname;
    this->CPUname=CPUname;
    this->arch=arch;
    this->username=username;
    this->cores=cores;
    this->maxMemory=maxMemory;
    this->availMemory=availMemory;
    this->useMemory=useMemory;
    this->procPeak=procPeak;
    this->procCurr=procCurr;
    this->disks=disks;

    enabledInfos["sysname"]=true;
    enabledInfos["arch"]=true;
    enabledInfos["cpuname"]=true;
    enabledInfos["cores"]=true;
    enabledInfos["username"]=true;
    enabledInfos["max_memory"]=true;
    enabledInfos["avail_memory"]=true;
    enabledInfos["use_memory"]=true;
    enabledInfos["proc_peak"]=true;
    enabledInfos["proc_curr"]=true;
    enabledInfos["disks"]=true;

    gather_info();

    infos["sysname"]=this->sysname;
    infos["arch"]=this->arch;
    infos["cpuname"]=this->CPUname;
    infos["cores"]=QString::number(this->cores);
    infos["username"]=this->username;
    infos["max_memory"]=QString::number(this->maxMemory);
    infos["avail_memory"]=QString::number(this->availMemory);
    infos["use_memory"]=QString::number(this->useMemory);
    infos["proc_peak"]=QString::number(this->procPeak);
    infos["proc_curr"]=QString::number(this->procCurr);
    QString tmp,tmp2;
    for(auto it = disks.begin();it!=disks.end();it++)
    {
        tmp2 = (*it).name;
        //tmp2.erase(tmp2.length()-1);
        tmp2 = tmp2.left(tmp2.count()-1);
        infos["disks"]+=tmp2;
        if(it!=disks.end()-1)
        {
            infos["disks"]+="|";
        }
        tmp = "max_";

        infos[tmp+tmp2] = QString::number((*it).totalSpace);
        tmp = "avail_";
        infos[tmp+tmp2] = QString::number((*it).freeSpace);
    }
}

int SYS_INFO::gather_sysname()
{
    this->sysname = QSysInfo::prettyProductName();
}

int SYS_INFO::gather_CPUname()
{
    /* do zmiany! */
        char CPUname[0x40];
        unsigned int CPUInfo[4] = {0,0,0,0};

        __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
        unsigned int nExIds = CPUInfo[0];

        memset(CPUname, 0, sizeof(CPUname));

        for (unsigned int i = 0x80000000; i <= nExIds; ++i)
        {
            __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

            if (i == 0x80000002)
                memcpy(CPUname, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000003)
                memcpy(CPUname + 16, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000004)
                memcpy(CPUname + 32, CPUInfo, sizeof(CPUInfo));
        }
        this->CPUname = CPUname;
    return 0;
}

int SYS_INFO::gather_arch()
{
    this->arch = QSysInfo::currentCpuArchitecture();
    return 0;
}

int SYS_INFO::gather_username()
{
#ifdef __WIN32
    char  lpBuffer[1024];
    LPDWORD pcbBuffer = new unsigned long(1024);
    if(!GetUserNameA(lpBuffer,pcbBuffer))
        std::cout<<"ERROR";
    this->username = lpBuffer;
#endif
#ifdef __linux__
    this->username = getlogin();
#endif
    return 0;
}

int SYS_INFO::gather_cores()
{
#ifdef __WIN32
    SYSTEM_INFO lps;
    GetSystemInfo(&lps);
    this->cores = lps.dwNumberOfProcessors;
#endif

#ifdef __linux__
    this->cores = get_nprocs();
#endif
    return 0;
}

int SYS_INFO::gather_max_memory()
{
#ifdef __WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);
    this->maxMemory = statex.ullTotalPhys;

#endif
#ifdef __linux__
    struct sysinfo info;
    sysinfo(&info);
    this->maxMemory = info.totalram;
#endif
    return 0;
}

int SYS_INFO::gather_avail_memory()
{
#ifdef __WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);
    this->availMemory = statex.ullAvailPhys;
#endif
#ifdef __linux__
    // do POPRAWY!
    QString cmd = "cat /proc/meminfo | grep \"memavailable:\" -i | grep -Eo \"[0-9]{0,256}\"";
    this->availMemory = QString::fromStdString(exec_cmd(cmd)).toLong()*1024;
#endif
    return 0;
}

int SYS_INFO::gather_use_memory()
{
    gather_max_memory();
    gather_avail_memory();
    this->useMemory = this->maxMemory-this->availMemory;
    return 0;
}

int SYS_INFO::gather_proc_peak()
{
#ifdef __WIN32
    PROCESS_MEMORY_COUNTERS PMCE;

    HANDLE hPinfo = GetCurrentProcess();
    GetProcessMemoryInfo(hPinfo,&PMCE,sizeof(PMCE));
    CloseHandle(hPinfo);
    this->procPeak = PMCE.PeakWorkingSetSize;
#endif
#ifdef __linux__
    struct rusage str;
    getrusage(RUSAGE_SELF,&str);
    this->procPeak = str.ru_maxrss;
#endif
    return 0;
}

int SYS_INFO::gather_proc_curr()
{
#ifdef __WIN32
    //sprawdzić, może poprawić
    PROCESS_MEMORY_COUNTERS_EX PMCE;

    HANDLE hPinfo = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                  PROCESS_VM_READ,
                                  FALSE, GetCurrentProcessId() );
    GetProcessMemoryInfo(hPinfo,reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&PMCE),sizeof(PMCE));
    CloseHandle(hPinfo);
    this->procCurr = PMCE.PrivateUsage;
#endif
#ifdef __linux__
    pid_t currID = getpid();
    char mypid[6];   // ex. 34567
    sprintf(mypid, "%d", currID);
    //std::cout<<"\ncurrent PID = "<<mypid<<"\n";
    QString cmd = "cat /proc/";
    cmd+=mypid;
    cmd+="/status | grep \"vmrss\" -i | grep -Eo \"[0-9]{0,256}\"";
    this->procCurr = QString::fromStdString(exec_cmd(cmd)).toLong();
#endif
    return 0;
}

int SYS_INFO::gather_disks_info()
{

    int number=0;
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes())
    {
        if (storage.isValid() && storage.isReady())
        {
            DISK_INFO di;
            if (!storage.isReadOnly())
            {
                #ifdef __WIN32
                   //qDebug()<<storage.displayName();
                   di.name=storage.displayName();
                #endif

                #ifdef __linux__
                   if(storage.device().contains("tmpfs"))
                   continue;
                di.name=storage.device().toStdString();
                #endif

                di.number=number;
                di.totalSpace=storage.bytesTotal();
                di.freeSpace=storage.bytesAvailable();
                di.usageSpace=di.totalSpace-di.freeSpace;
                this->disks.push_back(di);
                number++;
            }
        }
    }
    return 0;
}

int SYS_INFO::gather_info()
{
    if(enabledInfos["sysname"])
        gather_sysname();

    if(enabledInfos["cpuname"])
        gather_CPUname();

    if(enabledInfos["arch"])
        gather_arch();

    if(enabledInfos["username"])
        gather_username();

    if(enabledInfos["cores"])
        gather_cores();

    if(enabledInfos["disks"])
        gather_disks_info();

    if(enabledInfos["max_memory"])
        gather_max_memory();

    if(enabledInfos["avail_memory"])
        gather_avail_memory();

    if(enabledInfos["use_memory"])
        gather_use_memory();

    if(enabledInfos["proc_peak"])
        gather_proc_peak();

    if(enabledInfos["proc_curr"])
        gather_proc_curr();
    return 0;
}

/*QString SYS_INFO::gather_get(QString infoName)
{
    if(infoName=="sysname")
    {
        gather_sysname();
        return get_sysname();
    }

    return " ";
}*/

/*QVector<std::pair<QString,QString>> SYS_INFO::gather_get(QVector<QString> infoNames)
{
    return QVector<std::pair<QString,QString>>();
}*/

QString SYS_INFO::get_info(QString infoName)
{
    return infos[infoName];
}

QVector<QString> SYS_INFO::get_info(QVector<QString> infoNames)
{
    QVector<QString> res;
    if(infoNames.size()==0)
    {
        for(auto it = infos.begin();it!=infos.end();it++)
        {
            if(enabledInfos[it.key()])
                res.push_back(it.value());
        }
    }
    else
    {
        for(auto it = infoNames.begin();it!=infoNames.end();it++)
        {
            res.push_back(infos[*it]);
        }
    }
    return res;
}

QMap<QString,QString> SYS_INFO::get_info_map(QVector<QString> infoNames)
{
    QMap<QString,QString> res;
    if(infoNames.size()==0)
    {
        for(auto it = infos.begin();it!=infos.end();it++)
        {
            res[it.key()]=it.value();
        }
    }
    else
    {
        for(auto it = infoNames.begin();it!=infoNames.end();it++)
        {
            //res.push_back(infos[*it]);
            res[*it]=infos[*it];
        }
    }
    return res;
}

int SYS_INFO::set_enabled(QString infoname, bool enable)
{
    enabledInfos[infoname] = enable;
    return 0;
}

int SYS_INFO::set_enabled(QVector<QString> infoNames,bool enable)
{
    for(auto it = infoNames.begin();it!=infoNames.end();it++)
    {
        enabledInfos[*it] = enable;
    }
    return 0;
}

QVector<QString> SYS_INFO::listInfo()
{
    QVector<QString> res;
    res.push_back("sysname");
    res.push_back("arch");
    res.push_back("cpuname");
    res.push_back("cores");
    res.push_back("username");
    res.push_back("max_memory");
    res.push_back("avail_memory");
    res.push_back("use_memory");
    res.push_back("proc_peak");
    res.push_back("proc_curr");
    res.push_back("disks");
    res.push_back("avail_{DISK_VOLUME} --example: avail_C:");
    res.push_back("max_{DISK_VOLUME} --example: max_/dev/sda1");

    return res;
}

QString exec_cmd(QString &cmd)
{
    std::array<char, 128> buffer;
    QString result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.toStdString().c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
};

QDataStream& operator>>(QDataStream& in,SYS_INFO & fs)
{
    QMap<QString,bool> enabledInfos;
    QMap<QString,QString> infos;
    QString sysname,CPUname,arch,username;
    int cores;
    unsigned long long int maxMemory,availMemory,useMemory,procPeak,procCurr;
    QVector<DISK_INFO> disks;

    in>>enabledInfos;
    in>>infos;
    in>>sysname;
    in>>CPUname;
    in>>arch;
    in>>username;
    in>>cores;
    in>>maxMemory;
    in>>availMemory;
    in>>useMemory;
    in>>procPeak;
    in>>procCurr;
    in>>disks;

    fs = SYS_INFO(enabledInfos,infos,sysname,CPUname,arch,username,cores,maxMemory,availMemory,useMemory,
                  procPeak,procCurr,disks);
    return in;
}

QDataStream& operator<<(QDataStream& out,SYS_INFO &fs)
{
    out<<fs.get_enabled_infos();
    out<<fs.get_info_map();
    out<<fs.get_sysname();
    out<<fs.get_cpuname();
    out<<fs.get_arch();
    out<<fs.get_username();
    out<<fs.get_cores();
    out<<fs.get_max_memory();
    out<<fs.get_avail_memory();
    out<<fs.get_use_memory();
    out<<fs.get_proc_peak();
    out<<fs.get_proc_curr();
    out<<fs.get_disks_info();

    return out;
}

QDataStream& operator>>(QDataStream& in,DISK_INFO & fs)
{
    /*QString name;
    int number;
    qint64 totalSpace;
    qint64 usageSpace;
    qint64 freeSpace;*/

    in>>fs.name;
    in>>fs.number;
    in>>fs.totalSpace;
    in>>fs.usageSpace;
    in>>fs.freeSpace;

    return in;
}

QDataStream& operator<<(QDataStream& out,DISK_INFO const &fs)
{
    out<<fs.name;
    out<<fs.number;
    out<<fs.totalSpace;
    out<<fs.usageSpace;
    out<<fs.freeSpace;

    return out;
}
