#ifndef LOGS_LIBRARY_H
#define LOGS_LIBRARY_H

#include "logs_library_global.h"
#include <QDateTime>
#include <iostream>
#include <vector>
#include <map>
#include <QFileInfo>
#include <QTextStream>

class LOGS_LIBRARY_EXPORT LOG
{
private:
    std::string header,message,type,format;
    QDateTime date;
    std::vector<std::pair<std::string,std::string>> vCustoms;

public:
    LOG();
    LOG(QDateTime date) {this->date=date;};
    LOG(std::string header,std::string message,std::vector<std::pair<std::string,std::string>> custom);
    void set_message(std::string message)   {this->message=message;};
    void set_customs(std::vector<std::pair<std::string,std::string>> custom) {vCustoms=custom;};
    void add_custom(std::string tag, std::string message);
    void add_customs(std::vector<std::pair<std::string,std::string>> custom);
    void set_date(std::string date,std::string format);
    void set_date(QDateTime date)   {this->date=date;};
    void set_date_format(std::string format) {this->format=format;};
    void set_header(std::string header) {this->header=header;};
    void set_type(std::string type) {this->type=type;};
    std::string get_message() {return this->message;};
    std::string get_date(std::string format);
    QDateTime get_date();
    std::string get_header() {return this->header;};
    std::string get_type() {return this->type;};
    std::string get_date_format() {return this->format;};
};

class LOGS_LIBRARY_EXPORT FILE_STRUCT
{
private:
        bool newLineHeader = true;
        bool newLineElements = false;
        bool newLineFooter = true;
        std::vector<LOG> elements;
        std::map<std::string,std::string> tags;
        std::pair<std::string,std::string> braces;
        std::string header,footer,filePath;
public:
        FILE_STRUCT(std::string filePath,std::string header,std::string footer,std::vector<LOG> elements);

        void set_new_line_header(bool value) {newLineHeader=value;};
        void set_new_line_elements(bool value) {newLineElements=value;};
        void set_new_line_footer(bool value) {newLineFooter=value;};

        void set_elements(std::vector<LOG> logs) {elements=logs;};

        void set_tags(std::map<std::string,std::string> tags) {this->tags=tags;};
        void add_tags(std::string name,std::string value) {tags[name]=value;};
        void add_tags(std::string name) {tags[name]=name;};

        void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
        void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};

        int write(char mode = 'r');
};

class LOGS_LIBRARY_EXPORT LOGS
{
private:
    std::string login, fileName,path,mainHeader,header,format,footer,type;
    std::vector<LOG> logs;
    std::vector<std::pair<std::string,std::string>> customs;
    std::pair<std::string,std::string> braces;
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
    void add_msg(std::string message,std::string type);
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

#endif // LOGS_LIBRARY_H


