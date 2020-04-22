#include <QCoreApplication>
#include <../logs_library.h>
#include <QDebug>
#include <iostream>
//#include <cpuid.h>
#include <QSysInfo>
#include <QStorageInfo>
#include <QStandardPaths>
#include "../sys_info.h"

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
    #include <proc_service.h>
    #include <sys/sysinfo.h>
    #include <stdio.h>
#endif

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    //LOGS log;

    //log.save("D:\\test.txt");
 /*   SYS_INFO si;
   // si.gather_info();
    std::cout<<si.get_sysname()<<"----AND----"<<si.get_info("sysname")<<"\n";
    std::cout<<si.get_arch()<<"----AND----"<<si.get_info("arch")<<"\n";
    std::cout<<si.get_cpuname()<<"----AND----"<<si.get_info("cpuname")<<"\n";
    std::cout<<si.get_username()<<"----AND----"<<si.get_info("username")<<"\n";
    std::cout<<si.get_cores()<<"----AND----"<<si.get_info("cores")<<"\n";
    std::cout<<si.get_max_memory()<<"----AND----"<<si.get_info("max_memory")<<"\n";
    std::cout<<si.get_avail_memory()<<"----AND----"<<si.get_info("avail_memory")<<"\n";
    std::cout<<si.get_use_memory()<<"----AND----"<<si.get_info("use_memory")<<"\n";
    std::cout<<si.get_proc_peak()<<"----AND----"<<si.get_info("proc_peak")<<"\n";
    std::cout<<si.get_proc_curr()<<"----AND----"<<si.get_info("proc_curr")<<"\n";
    std::cout<<"----AND----"<<si.get_info("disks")<<"\n";
    std::cout<<si.get_disks_info()[0].name<<"\n";
    std::cout<<"\t"<<si.get_disks_info()[0].totalSpace<<"\t"<<si.get_disks_info()[0].freeSpace<<"\t"<<si.get_disks_info()[0].usageSpace<<"\n";
    std::cout<<si.get_disks_info()[1].name<<"\n";
    std::cout<<"\t"<<si.get_disks_info()[1].totalSpace<<"\t"<<si.get_disks_info()[1].freeSpace<<"\t"<<si.get_disks_info()[1].usageSpace<<"\n";
/*
#ifdef __WIN32
    char  lpBuffer[1024];
    LPDWORD pcbBuffer = new unsigned long(1024);
    if(!GetUserNameA(lpBuffer,pcbBuffer))
        std::cout<<"ERROR";

   std::cout<<lpBuffer;

   MEMORYSTATUSEX statex;
   statex.dwLength = sizeof (statex);

     GlobalMemoryStatusEx (&statex);
   std::cout<<"\n============\n";
   std::cout<<(double) statex.ullTotalPhys/1024/1024/1024;
   std::cout<<"\n============\n";
std::cout<<(double) statex.ullAvailPhys/1024/1024/1024;

    PROCESS_MEMORY_COUNTERS PMCE[1];

    HANDLE hPinfo = GetCurrentProcess();
    GetProcessMemoryInfo(hPinfo,PMCE,sizeof(PMCE));
    CloseHandle(hPinfo);
   std::cout<<"\n============\n";
  // std::cout<<PMCE->WorkingSetSize;
#endif

   for(;;)
   {
       si.gather_info();
       std::cout<<si.get_proc_peak()<<"\n";
       PROCESS_MEMORY_COUNTERS PMCE;

       HANDLE hPinfo = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                     PROCESS_VM_READ,
                                     FALSE, GetCurrentProcessId() );
       GetProcessMemoryInfo(hPinfo,&PMCE,sizeof(PMCE));
       PSIZE_T coss,cos;
       GetProcessWorkingSetSize(hPinfo,coss,cos);
       std::cout<<*cos<<"\n";
       CloseHandle(hPinfo);
       Sleep(2200);
   };
*/
/*
    std::vector<std::string> dsd = si.get_info(std::vector<std::string>({"sysname","arch","max_memory"}));
    for(auto it=dsd.begin();it!=dsd.end();it++)
    {
        std::cout<< *it <<std::endl;
    }*/

    XML fileXML;
    LOGS logs;
    logs.add("",QDateTime::currentDateTime().toString("dd.MM.yyyy").toStdString(),"dd.MM.yyyy","jakas wiadomosc");
   /* logs.add("",QDateTime::currentDateTime().toString("dd.MM.yyyy").toStdString(),"dd.MM.yyyy","jakas wiadomosc");
    logs.add("",QDateTime::currentDateTime().toString("dd.MM.yyyy").toStdString(),"dd.MM.yyyy","jakas wiadomosc");
    logs.add("",QDateTime::currentDateTime().toString("dd.MM.yyyy").toStdString(),"dd.MM.yyyy","jakas wiadomosc");*/

    logs.save("D:\\test2.xml");
    logs.autosave_start("D:\\testy.xml");

    std::map<QString,QString> mmap;
    mmap["date"] = logs.get_LOG(0)->get_date().toString("dd.MM.yyyy");
    mmap["content"] = QString::fromStdString(logs.get_LOG(0)->get_message());
    std::vector<std::map<QString,QString>> logi;

    logi.push_back(mmap);
    logi.push_back(mmap);
    logi.push_back(mmap);
    logi.push_back(mmap);

    SYS_INFO si;
    QFile test("D:\\test.xml");
    test.open(QFile::WriteOnly | QFile::Text);
    std::cout<<fileXML.start_file("to tylko testy");
    std::cout<<fileXML.sys_info(si.get_info_map());
    std::cout<<fileXML.log(logi);
    std::cout<<fileXML.end_file();
    test.write(fileXML.start_file("to tylko testy").c_str());
    test.write(fileXML.sys_info(si.get_info_map()).c_str());
    test.write(fileXML.log(logi).c_str());
    test.write(fileXML.end_file().c_str());
    test.close();
    logs.set_autosave_time(4);
    for(int i=0;;i++)
    {

        if(i==200000)
        {
            logs.autosave_stop();
            break;
        }
        if(i%10000==0)
        {
            Sleep(1000);
            logs.add("",QDateTime::currentDateTime().toString("dd.MM.yyyy").toStdString(),"dd.MM.yyyy","jakas wiadomosc");
            std::cout<<i<<std::endl;
        }
    }
    return 0;
}

