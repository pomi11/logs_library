#ifndef LOG_H
#define LOG_H

#include <QDateTime>

class LOG
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

#endif // LOG_H
