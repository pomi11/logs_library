#include <QCoreApplication>
#include <../logs_library.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    LOG log;
    return a.exec();
}
