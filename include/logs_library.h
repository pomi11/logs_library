#ifndef LOGS_LIBRARY_H
#define LOGS_LIBRARY_H

#include "logs_library_global.h"
#include <QDateTime>
#include <iostream>
#include <vector>
#include <map>
#include <QFileInfo>
#include <QTextStream>
#include "logs.h"




/*
class LOGS_LIBRARY_EXPORT LOGS
{
private:
    std::string login, fileName,path,mainHeader,header,format,footer,type;
    QVector<LOG> logs;
    QVector<std::pair<std::string,std::string>> customs;
    std::pair<std::string,std::string> braces;
    int autoSaveTime = 0;
public:
    LOGS();
    LOGS(std::string fileName) {this->fileName = fileName;};
    LOGS(std::string fileName,std::string path) {this->fileName=fileName;this->path=path;};
    LOGS(QVector<LOG> logs) {this->logs = logs;};
    LOGS(std::string fileName,QVector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(std::string header,std::string date,std::string format,std::string message);
    void add(std::string header,QDateTime date,std::string message);
    void add(std::string header,std::string date,std::string format,std::string message,QVector<std::pair<std::string,std::string>> customs);
    void add(std::string header,QDateTime,std::string message,QVector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message);
    void add_msg(std::string message,std::string type);
    void add_msg(std::string message, QDateTime date);
    void add_msg(std::string message,std::string date,std::string format);
    void add_msg(std::string message,QVector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message,std::string date,std::string format,QVector<std::pair<std::string,std::string>> customs);

    void remove(int index);
    void remove(std::string message, bool all=true, bool first=false,bool last=false);
    void remove_by_date(std::string date, std::string format, bool all=true, bool first=false,bool last=false);
    void remove_by_date(QDateTime date, bool all=true, bool first=false,bool last=false);

    //void replace(LOG log, LOG log2);

    void change_message(int index, std::string newMessage);

    LOG* get_LOG(int index);
    LOG* get_LOG(std::string message, bool reverse=false);
    LOG* get_LOG(std::string date,std::string format, bool reverse=false);
    LOG* get_LOG(QDateTime date, bool reverse=false);

    QVector<LOG> get_LOGs();
    QVector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);
    QVector<LOG> get_LOGs(std::string message);
    QVector<LOG> get_LOGs_by_date(std::string date,std::string format);
    QVector<LOG> get_LOGs_by_date(QDateTime date);
   // QVector<LOG> get_LOGs_by_date();

    void set_file_name(std::string fileName) {this->fileName=fileName;};
    void set_file_path(std::string path) {this->path=path;};

    void set_date_format(std::string format) {this->format=format;};
    void set_main_header(std::string header) {this->mainHeader=header;};
    void set_footer(std::string footer) {this->footer=footer;};
    void set_default_type(std::string type) {this->type=type;};

    int save(char mode='r'); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave_start();
    void autosave_start(int autoSaveTime);
    void set_autosave_time(int time) {this->autoSaveTime=time;};
    void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
    void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};
};
*/

#endif // LOGS_LIBRARY_H


