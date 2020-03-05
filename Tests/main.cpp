#include <QCoreApplication>
#include <../logs_library.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LOGS log;

    log.set_file_name("D:\\test.txt");
    log.set_date_format("dd//MM//yyyy");
    log.set_main_header("PIERWSZY TEST");
    log.set_footer("KONIEC!!!");
    log.set_default_type("NORMAL");
    log.set_braces("[","]");
    log.add_msg("LOG_1");
    log.add_msg("LOG_2","ERROR");
    log.add_msg("LOG_3","INFO");
    log.add_msg("LOG_45","WARNING");
    log.add_msg("LOG_255","ERROR");
    log.add_msg("LOG_22","CRITICAL");
    log.save();
    std::cout<<"koniec?";
    return a.exec();
}

