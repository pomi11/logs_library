#ifndef LOGS_LIBRARY_H
#define LOGS_LIBRARY_H

#include "logs_library_global.h"
#include <QDateTime>
#include <iostream>
#include <vector>
//#include <map>
#include <QFileInfo>

class LOGS_LIBRARY_EXPORT LOG
{
private:
    std::string sHeader,sMessage;
    QDateTime date;
    std::vector<std::pair<std::string,std::string>> vCustoms;

public:
    LOG();
    LOG(QDateTime date) {this->date=date;};
    LOG(std::string header,std::string message,std::vector<std::pair<std::string,std::string>> custom);
    void set_message(std::string message)   {this->sMessage=message;};
    void set_customs(std::vector<std::pair<std::string,std::string>> custom) {vCustoms=custom;};
    void add_custom(std::string tag, std::string message);
    void add_customs(std::vector<std::pair<std::string,std::string>> custom);
    void set_date(std::string date,std::string format);
    void set_date(QDateTime date)   {this->date=date;};
    void set_header(std::string header) {this->sHeader=header;};
    std::string get_message() {return this->sMessage;};
    std::string get_date(std::string format);
    QDateTime get_date();
};

/*class LOGS_LIBRARY_EXPORT FILE_STUCT
{

};
*/

class LOGS_LIBRARY_EXPORT LOGS
{
private:
    std::string login, fileName,path,mainHeader,header;
    std::vector<LOG> logs;
    std::vector<std::pair<std::string,std::string>> customs;
    int autoSaveTime = 0;
public:
    LOGS();
    LOGS(std::string fileName) {this->fileName = fileName;};
    LOGS(std::string fileName,std::string path) {this->fileName=fileName;this->path=path;};
    LOGS(std::vector<LOG> logs) {this->logs = logs;};
    LOGS(std::string fileName,std::vector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(std::string header,std::string date,std::string format,std::string message);
    void add(std::string header,QDateTime date,std::string message);
    void add(std::string header,std::string date,std::string format,std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add(std::string header,QDateTime,std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message);
    void add_msg(std::string message, QDateTime date);
    void add_msg(std::string message,std::string date,std::string format);
    void add_msg(std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message,std::string date,std::string format,std::vector<std::pair<std::string,std::string>> customs);

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

    std::vector<LOG> get_LOGs();
    std::vector<LOG> get_LOGs(int indexFrom = 0, int indexTo = 0);
    std::vector<LOG> get_LOGs(std::string message);
    std::vector<LOG> get_LOGs_by_date(std::string date,std::string format);
    std::vector<LOG> get_LOGs_by_date(QDateTime date);
   // std::vector<LOG> get_LOGs_by_date();

    void set_file_name(std::string fileName) {this->fileName=fileName;};
    void set_file_path(std::string path) {this->path=path;};

    int save(char mode='r'); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave_start();
    void autosave_start(int autoSaveTime);
    void set_autosave_time(int time) {this->autoSaveTime=time;};
};

#endif // LOGS_LIBRARY_H


