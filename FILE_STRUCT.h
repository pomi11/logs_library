#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include "logs_library_global.h"
#include <iostream>
#include <vector>
#include <map>
#include "log.h"

class LOGS_LIBRARY_EXPORT FILE_STRUCT
{
/*protected:
    bool newLineHeader = true;
    bool newLineElements = false;
    bool newLineFooter = true;
    QVector<LOG> elements;
    QMap<std::string,std::string> tags;
    std::pair<std::string,std::string> braces;
    std::string header,footer,filePath;*/
public:
    /*FILE_STRUCT(std::string filePath,std::string header,std::string footer,QVector<LOG> elements);

    void set_new_line_header(bool value) {newLineHeader=value;};
    void set_new_line_elements(bool value) {newLineElements=value;};
    void set_new_line_footer(bool value) {newLineFooter=value;};

    void set_elements(QVector<LOG> logs) {elements=logs;};

    void set_tags(QMap<std::string,std::string> tags) {this->tags=tags;};
    void add_tags(std::string name,std::string value) {tags[name]=value;};
    void add_tags(std::string name) {tags[name]=name;};

    void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
    void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};

    int write(char mode = 'r');*/

    virtual std::string start_file(QString description) = 0;
    virtual std::string sys_info(QMap<QString,QString> sysInfo) = 0;
    virtual std::string log(QVector<QMap<QString,QString>> logs) = 0;
    virtual std::string end_file() = 0;

};

class XML: public FILE_STRUCT
{
private:
    QVector<QString> tags;
    //std::string file_header();
    bool isNumLog=true, isSysSum=true,isFileDescr=true,isFileDate=true;
public:
    XML(QString header,QString footer);
    XML();
    std::string log(QVector<QMap<QString,QString>> logs)  override;
    std::string end_file() override;
    std::string start_file(QString description) override;
    std::string sys_info(QMap<QString,QString> sysInfo) override;

    void show_num_log(bool enable) {isNumLog=enable;};
    void show_file_date(bool enable) {isFileDate=enable;};
    void show_file_descr(bool enable) {isFileDescr=enable;};
    void show_sys_info(bool enable) {isSysSum=enable;};
    void set_tags(QVector<QString> list){tags=list;};

    bool is_num_log() {return isNumLog;};
    bool is_file_date() {return isFileDate;};
    bool is_file_descr() {return isFileDescr;};
    bool is_sys_info() {return isSysSum;};

    QVector<QString> get_tags(){return this->tags;};


    int set_file_header(std::string header);
    /*int set_log_header(std::string header);*/
};

class TXT: public FILE_STRUCT
{
public:
    TXT(QString header,QString footer);
    TXT();
    std::string log(QVector<QMap<QString,QString>> logs)  override;
    std::string end_file() override;
    std::string start_file(QString description) override;
};

LOGS_LIBRARY_EXPORT QDataStream& operator>>(QDataStream& in,XML *& fs);
LOGS_LIBRARY_EXPORT QDataStream& operator<<(QDataStream& out,XML &fs);

#endif // FILE_STRUCT_H
