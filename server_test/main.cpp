#include <QCoreApplication>
#include "../directserver.h"
#include <QDebug>

void start()
{

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

 /*   QString filePath = "D:\\";
    QString filePath2 = "jakis.txt";
    QString fileExt = filePath2.mid(filePath2.length()-4);
    QString fileName2 = filePath2.left(filePath2.length()-4);
    fileName2 +="_"+QString::number(1);
    filePath +=fileName2+fileExt;
    qDebug()<<fileExt;
    qDebug()<<fileName2;
    qDebug()<<filePath;*/
    DirectServer *ds = new DirectServer();
    ds->set_pwd("test");
    ds->set_user("jakis");
    ds->set_save_dir("D:\\");

    return a.exec();
}
