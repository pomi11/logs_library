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
    DATE,
    NONE
};

class LOGS_LIBRARY_EXPORT DirectServer : public QObject
{
    Q_OBJECT
private:
    int logNum = 0;
    QTcpServer *control, *data;
    QVector<QTcpSocket*> clients;
    QVector<QTcpSocket*> acceptedClients;
    QVector<QTcpSocket*> dataClients;
    QString saveDir,username,password, fileName,userTMP,passTMP;
    LOGS *logs = nullptr;
    FILE_STRUCT *fs = nullptr;
    FILE_EXT fe = NUMBERS;
    QString currentCMD="";
    int save();
    bool isAccepted(QString sck);
    qint16 controlPort,dataPort;
public:
    DirectServer();
    //void incomingConnection(qintptr handle) override;
    void set_save_dir(QString dir) {saveDir=dir;};
    void set_user(QString username) {this->username=username;};
    void set_pwd(QString pwd) {password=pwd;};
    void set_file_name(QString file) {fileName=file;};
    void set_file_struct(FILE_STRUCT *fileStruct) {fs=fileStruct;};
    void set_file_ext(FILE_EXT fe) {this->fe=fe;};
    void set_control_port(quint16 port) {controlPort=port;control->close();control->listen(QHostAddress::Any,port);};
    void set_data_port(quint16 port) {dataPort=port;control->close();data->listen(QHostAddress::Any,port);};

    FILE_STRUCT *get_file_struct() {return fs;};


public slots:
    void controlService();
    void dataService();
    void disconnectedSocket();
    void newControlConn();
    void newDataConn();
};
#endif // DIRECTSERVER_H
