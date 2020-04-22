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
    /*bool newLineHeader = true;
    bool newLineElements = false;
    bool newLineFooter = true;
    std::vector<LOG> elements;
    std::map<std::string,std::string> tags;
    std::pair<std::string,std::string> braces;
    std::string header,footer,filePath;*/
public:
    /*FILE_STRUCT(std::string filePath,std::string header,std::string footer,std::vector<LOG> elements);

    void set_new_line_header(bool value) {newLineHeader=value;};
    void set_new_line_elements(bool value) {newLineElements=value;};
    void set_new_line_footer(bool value) {newLineFooter=value;};

    void set_elements(std::vector<LOG> logs) {elements=logs;};

    void set_tags(std::map<std::string,std::string> tags) {this->tags=tags;};
    void add_tags(std::string name,std::string value) {tags[name]=value;};
    void add_tags(std::string name) {tags[name]=name;};

    void set_braces(std::string start,std::string end) {this->braces=std::make_pair(start,end);};
    void set_braces(std::pair<std::string,std::string> braces) {this->braces=braces;};

    int write(char mode = 'r');*/

    virtual std::string start_file(QString description) = 0;
    virtual std::string sys_info(std::map<QString,QString> sysInfo) = 0;
    virtual std::string log(std::vector<std::map<QString,QString>> logs) = 0;
    virtual std::string end_file() = 0;

};

class XML: public FILE_STRUCT
{
private:
    std::vector<std::string> tags;
    std::string file_header();
    bool isNumLog=true, isSysSum=true,isFileDescr=true,isFileDate=true;
public:
    XML(QString header,QString footer);
    XML();
    std::string log(std::vector<std::map<QString,QString>> logs)  override;
    std::string end_file() override;
    std::string start_file(QString description) override;
    std::string sys_info(std::map<QString,QString> sysInfo) override;

    void show_num_log(bool enable) {isNumLog=enable;};
    void show_file_date(bool enable) {isFileDate=enable;};
    void show_file_descr(bool enable) {isFileDescr=enable;};
    void show_sys_info(bool enable) {isSysSum=enable;};

    int set_file_header(std::string header);
    /*int set_log_header(std::string header);*/
};

class TXT: public FILE_STRUCT
{
public:
    TXT(QString header,QString footer);
    TXT();
    std::string log(std::vector<std::map<QString,QString>> logs)  override;
    std::string end_file() override;
    std::string start_file(QString description) override;
};

#endif // FILE_STRUCT_H
