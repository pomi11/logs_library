#include <QCoreApplication>
#include <../logs_library.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LOGS log;

    log.set_file_name("D:\\test.txt");
    log.save();
    qDebug()<<"koniec?";
    return a.exec();
}

