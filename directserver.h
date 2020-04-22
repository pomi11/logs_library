#ifndef DIRECTSERVER_H
#define DIRECTSERVER_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>
#include "logs.h"

enum RETURN_CODE
{
    ACC,
    WPWD,
    WUSR,
    GOT
};

enum FILE_EXT
{
    NUMBERS,
    DATE
};

class LOGS_LIBRARY_EXPORT DirectServer : public QObject
{
    Q_OBJECT
private:
    int logNum = 0;
    QTcpServer *control, *data;
    std::vector<QTcpSocket*> clients;
    std::vector<QTcpSocket*> acceptedClients;
    QString saveDir,username,password, fileName;
    LOGS *logs = nullptr;
    FILE_STRUCT *fs = nullptr;
    FILE_EXT fe = NUMBERS;

public:
    DirectServer();
    //void incomingConnection(qintptr handle) override;
    void set_save_dir(QString dir) {saveDir=dir;};
    void set_user(QString username) {this->username=username;};
    void set_pwd(QString pwd) {password=pwd;};
    void set_file_name(QString file) {fileName=file;};
    void set_file_struct(FILE_STRUCT *fileStruct) {fs=fileStruct;};
    void set_file_ext(FILE_EXT fe) {this->fe=fe;};

    int save();
public slots:
    void controlService();
    void dataService();
    void newControlConn();
    void newDataConn();
};

/*
class DirectThread : public QThread
{
    Q_OBJECT

public:
    DirectThread(int socketDescriptor, const QString &fortune, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};
*/
#endif // DIRECTSERVER_H
