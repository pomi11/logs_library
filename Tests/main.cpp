#include <QCoreApplication>
#include "logs.h"
//#include "iconnector.h"
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
    log.set_default_type("INFORMATION");
    log.set_file_name("testowy.xml");
    log.set_file_path("D:\\");
    log.set_date_format("dd-MM-yy hh:mm:ss");
    log.set_default_type("NORMAL");
    log.set_default_header("TO JEST NAGLOWEK");
    log.show_log_proc_memory_usage(true);
    log.show_log_type(true);
    log.show_file_date(true);
    log.show_log_header(true);
    log.show_log_memory_avail(true);
    log.show_log_memory_usage(true);
    log.show_log_proc_memory_max(true);
    log.show_log_date(true);
    log.show_log_number(true);
    log.show_sys_summary(true);
    //log.show
    /*log.add_msg("test1");
    log.add_msg("test2");
    log.add_msg("test3");
    log.add_msg("test3");
    log.add_msg("test4","ERROR");
    SYS_INFO si;
    log.set_custom_log_sys_info(si);
    log.add_msg("test4","WARNING");
    LOG l;
    l.set_message("WAZNY");
    l.set_type("TAKISOBIEWAZNYMOCNOZEAZROZWALAMOZG");
    QList<LOG> sz;
    for(int i=0;i<10;i++)
    {
        sz.push_back(l);
    }

    log.add(sz);*/
    //log.add("header",QDateTime::currentDateTime(),"test");
    //log.add("header",QDateTime::currentDateTime(),"test2");
    //log.add("header",QDateTime::currentDateTime(),"test3");
    //log.add("header",QDateTime::currentDateTime(),"test4");

    int i =0;
    QTcpSocket s,s2;
    DirectConnection dc;
    log.autosave_start(1);
    SYS_INFO si;
    si.set_enabled();
    si.gather_info();
    //log.set_custom_log_sys_info(si);
    QString cccc = "To jest log "+QString::number(i);
    log.set_autolog_message(&cccc);
    log.autolog_start(1);
    log.connect_to_log_serv("localhost",1616,"jakis","test");
    log.save();

   /* dc.send_data(log);
    log.add("header",QDateTime::currentDateTime(),"test5");
    log.add("header",QDateTime::currentDateTime(),"test6");
    QVector<LOG> logi = log.get_LOGs(0);
   // dc.send_data(logi);
    dc.close();*/



    QFile f("D:\\d.xml");
    f.open(QFile::WriteOnly | QFile::Text);

    f.write("test");
    f.write("dalej\nasdasd");
    f.write("powinnybyc2");
    f.close();
    unsigned long long int is=0;
    while(1)
    {
        cccc = "To jest log "+QString::number(i);
        Sleep(500);
        if(is==10)
        {
            log.autolog_stop();
            log.autosave_stop();
        }
        else
        {
            log.add_msg("WIADOMOSC RECZNA");
            qDebug()<<is;
        }
        is++;
        i++;
    }
    qDebug()<<"KONIEC!";
    return a.exec();
}

