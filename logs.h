#ifndef LOGS_H
#define LOGS_H

#include "file_struct.h"
#include "sys_info.h"
#include <thread>
#include <QtConcurrent/QtConcurrent>

class LOGS
{
private:
    std::string login, fileName,path,mainHeader,header,format,footer,type;
    std::vector<LOG> logs;
    std::map<QString,QString> customs;
    std::pair<std::string,std::string> braces;
    int autoSaveTime = 10;
    FILE_STRUCT* fs; // do ogarnięcia temat wycieku pamięci ewentualny
    std::thread *thread;
    bool stop = false;
public:
    LOGS();
    LOGS(std::string fileName) {this->fileName = fileName;};
    LOGS(std::string fileName,std::string path) {this->fileName=fileName;this->path=path;};
    LOGS(std::vector<LOG> logs) {this->logs = logs;};
    LOGS(std::string fileName,std::vector<LOG> logs) {this->fileName = fileName;this->logs = logs;};

    void add(LOG log);
    void add(std::string header,std::string date,std::string format,std::string message);
    void add(std::string header,QDateTime date,std::string message);
    void add(std::string header,std::string date,std::string format,std::string message,std::map<QString,QString> customs);
    void add(std::string header,QDateTime,std::string message,std::map<QString,QString> customs);

    /*void add_msg(std::string message);
    void add_msg(std::string message,std::string type);

    void add_msg(std::string message,QDateTime date);
    void add_msg(std::string message,std::string date,std::string format);

    void add_msg(std::string message,std::vector<std::pair<std::string,std::string>> customs);
    void add_msg(std::string message,std::string date,std::string format,std::vector<std::pair<std::string,std::string>> customs);*/

    //void add_msg(std::string message,std::string type="", std::string header = "", std::string date="",std::string format="",std::vector<std::pair<std::string,std::string>> customs={});
    void add_msg(std::string message,std::string type="", std::string header = "", QDateTime date=QDateTime(),std::string format="",std::map<QString,QString> customs={});

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

    int save(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr); // w - zapisz bez nadpisywania(jeśli plik istnieje, robi nowy z nazwa_1), r - z nadpisywaniem, q - zapytaj, a - dopisz do istniejącego pliku

    void autosave(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_start(int autoSaveTime,QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_start(QString filePath, char mode='r',FILE_STRUCT *file_struct = nullptr);
    void autosave_stop();
    void set_autosave_time(int time) {this->autoSaveTime=time;};
    void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
    void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};
};

#endif // LOGS_H
