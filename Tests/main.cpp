#include <QCoreApplication>
#include "logs.h"
#include "iconnector.h"
#include <QTcpSocket>
//#include "../sys_info.h"
//#include "directserver.h"
//#include "datastreamextension.h"


/*#ifdef __WIN32
    #include <sysinfoapi.h>
    #include <windef.h>
    #include <winbase.h>
    #include <psapi.h>
#endif
*/
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
    QCoreApplication a(argc, argv);
    LOGS log;
    log.add("header",QDateTime::currentDateTime(),"test");
    log.add("header",QDateTime::currentDateTime(),"test2");
    log.add("header",QDateTime::currentDateTime(),"test3");
    log.add("header",QDateTime::currentDateTime(),"test4");
    int i =0;
    QTcpSocket s,s2;
    DirectConnection dc;

    dc.connect("localhost",1616,"jakis","test");

    dc.send_data(log);
    log.add("header",QDateTime::currentDateTime(),"test5");
    log.add("header",QDateTime::currentDateTime(),"test6");
    QVector<LOG> logi = log.get_LOGs(0);
    dc.send_data(logi);
    dc.close();

    qDebug()<<"KONIEC!";

    return a.exec();
}

