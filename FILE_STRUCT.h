#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <iostream>
#include <vector>
#include <map>
#include "log.h"

class FILE_STRUCT
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

    virtual std::string start_file() = 0;
    virtual std::string log(QString header = "",QString content = "", QDateTime date = QDateTime()) = 0;
    virtual std::string end_file() = 0;

};

class XML: public FILE_STRUCT
{
private:
    std::vector<std::string> tags;
public:
    XML(QString header,QString footer);
    XML();
    std::string log(QString header = "",QString content = "", QDateTime date = QDateTime())  override;
    std::string end_file() override;
    std::string start_file() override;

    int set_file_header(std::string header);
    int set_log_header(std::string header);
};

class TXT: public FILE_STRUCT
{
public:
    TXT(QString header,QString footer);
    TXT();
    std::string log(QString header = "",QString content = "", QDateTime date = QDateTime())  override;
    std::string end_file() override;
    std::string start_file() override;
};

#endif // FILE_STRUCT_H
