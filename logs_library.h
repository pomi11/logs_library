#ifndef LOGS_LIBRARY_H
#define LOGS_LIBRARY_H

#include "logs_library_global.h"
#include <QDateTime>
#include <iostream>
#include <vector>
#include <map>

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
};

/*class LOGS_LIBRARY_EXPORT FILE_STUCT
{

};
*/

class LOGS_LIBRARY_EXPORT LOGS
{
private:
    std::string login;
public:
    LOGS();
};

#endif // LOGS_LIBRARY_H
