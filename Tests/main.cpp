#include <QCoreApplication>
#include <../logs_library.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDateTime qdt = QDateTime::currentDateTime();


    QDateTime afw = QDateTime::fromString(QDateTime::currentDateTime().toString("dd:MMMM:yyyy//HH:mm:ss"),"dd:MMMM:yyyy//HH:mm:ss");
    QDate dd= QDate::fromString()
    qDebug()<<afw;
    return a.exec();
}
