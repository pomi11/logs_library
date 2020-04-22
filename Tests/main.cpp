#include <QCoreApplication>
#include <../logs_library.h>
#include <QDebug>
#include <iostream>
//#include <cpuid.h>
#include <QSysInfo>
#include <QStorageInfo>
#include <QStandardPaths>
#include "../sys_info.h"
#include "../directserver.h"


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
    QCoreApplication a(argc, argv);

    int i =0;
    while(1)
    {
        Sleep(2000);
        qDebug()<<"lte's go";
        QTcpSocket s;
        QTcpSocket s2;
        s.connectToHost("localhost",1616);
        s2.connectToHost("localhost",1616);
        qDebug()<<s.waitForConnected(2000);
        QString d = "to jest "+QString::number(i)+"\r\n";
        s.write(d.toStdString().c_str());
        s.waitForBytesWritten(20000);
        d = "SECOND "+QString::number(i)+"\r\n";
        qDebug() << s.waitForReadyRead();
        s.write(d.toStdString().c_str());
        s.waitForBytesWritten(20000);
        Sleep(1000);
        s.close();
        i++;
    }

    return a.exec();
}

