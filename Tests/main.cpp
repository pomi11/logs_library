#include <QCoreApplication>
#include "logs.h"
#include <QTcpSocket>
//#include <watcher.h>

/*#include <../boost/convert.hpp>
#include <../boost/convert/lexical_cast.hpp>
#include <../boost/convert/base.hpp>
#include <../boost/cast.hpp>
#include <string>*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   // QString d = "test";
    LOGS c;
 /*   int g = 0;
    //RealWatcher<QString> asd(&d);
    RealWatcher<int> asd(&g);
    QString da = QString("d");
    QString dd = QString("ds");
    QString dd1 = QString("ds1");
    QString dd2 = QString("ds2");
    int h = 0;
    int gh = 0;
    int xd = 0;
    c.watch(da,&g/*,&asd*//*);
    c.watch(dd,&h);
    c.watch(dd1,&gh);
    c.watch(dd2,&xd);
   // QString dob = "asd";

    //boost::conv
   // qDebug()<<"?";
   while(1)
    {
        Sleep(1);
       // c.add_msg("testfasdfasdfsadfsdafasdfasdfdsafasdfsadfasdfasdfasdfasdfasdfsadfsad");
        //qDebug()<<"asd";
        if(g==100)
        {
            c.stop_watch(da);
            c.stop_watch(dd);
            c.stop_watch(dd1);
            c.stop_watch(dd2);
            break;
        }
        g+=1;
        h+=1;
        gh++;
        xd++;
    }

   // QThread::sleep(4);
    qDebug()<<"and..."<<c.get_LOGs(0).count();

    c.save("D:\\s.xml");

*/
    c.add_msg("test");
    c.add_msg("test2");
    c.add_msg("test3");

    c.connect_to_log_serv("localhost",1616,"jakis","test");

    c.save();
    return a.exec();
}

