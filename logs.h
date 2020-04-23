#ifndef LOGS_H
#define LOGS_H

#include "logs_library_global.h"
#include "file_struct.h"
#include "sys_info.h"
#include <thread>
#include <QtConcurrent/QtConcurrent>

class LOGS_LIBRARY_EXPORT LOGS
{
private:
    QString login, fileName,path,mainHeader,header,format,footer,type;
    QVector<LOG> logs;
    QMap<QString,QString> customs;
    //std::pair<QString,QString> braces;
    int autoSaveTime = 10;
    FILE_STRUCT* fs; // do ogarnięcia temat wycieku pamięci ewentualny
    SYS_INFO *si;
   // std::thread *thread;
    bool stop = false;
public:
    LOGS();
    LOGS(QString fileName) {this->fileName = fileName;};
    LOGS(QString fileName,QString path) {this->fileName=fileName;this->path=path;};
    LOGS(QVector<LOG> logs) {this->logs = logs;};
    LOGS(QString fileName,QVector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(QString header,QString date,QString format,QString message);
    void add(QString header,QDateTime date,QString message);
    void add(QString header,QString date,QString format,QString message,QMap<QString,QString> customs);
    void add(QString header,QDateTime,QString message,QMap<QString,QString> customs);

    /*void add_msg(QString message);
    void add_msg(QString message,QString type);

    void add_msg(QString message,QDateTime date);
    void add_msg(QString message,QString date,QString format);

    void add_msg(QString message,QVector<std::pair<QString,QString>> customs);
    void add_msg(QString message,QString date,QString format,QVector<std::pair<QString,QString>> customs);*/

    //void add_msg(QString message,QString type="", QString header = "", QString date="",QString format="",QVector<std::pair<QString,QString>> customs={});
    void add_msg(QString message,QString type="", QString header = "", QDateTime date=QDateTime(),QString format="",QMap<QString,QString> customs={});

    void remove(int index);
    void remove(QString message, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QString date, QString format, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QDateTime date, bool all=true, bool first=false,bool last=false);

    //void replace(LOG log, LOG log2);

    void change_message(int index, QString newMessage);

    LOG* get_LOG(int index);
    LOG* get_LOG(QString message, bool reverse=false);
    LOG* get_LOG(QString date,QString format, bool reverse=false);
    LOG* get_LOG(QDateTime date, bool reverse=false);

    QVector<LOG> get_LOGs();
    QVector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);
    QVector<LOG> get_LOGs(QString message);
    QVector<LOG> get_LOGs_by_date(QString date,QString format);
    QVector<LOG> get_LOGs_by_date(QDateTime date);
    // QVector<LOG> get_LOGs_by_date();

    QString get_file_name() {return fileName;};
    QString get_file_path() {return path;};
    QString get_main_header() {return mainHeader;};
    QString get_date_format() {return format;};
    QString get_footer()    {return footer;};
    QString get_default_type() {return type;};
    FILE_STRUCT *get_file_struct() {return fs;};

    void set_file_name(QString fileName) {this->fileName=fileName;};
    void set_file_path(QString path) {this->path=path;};

    void set_date_format(QString format) {this->format=format;};
    void set_main_header(QString header) {this->mainHeader=header;};
    void set_footer(QString footer) {this->footer=footer;};
    void set_default_type(QString type) {this->type=type;};

    int save(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_start(int autoSaveTime,QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_start(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_stop();
    void set_autosave_time(int time) {this->autoSaveTime=time;};
    //void set_braces(QString start,QString end) {this->braces=std::make_pair(start,end);};
    //void set_braces(std::pair<QString,QString> braces) {this->braces=braces;};
};

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,LOGS &fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,LOGS &fs);

#endif // LOGS_H
