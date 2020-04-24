#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>
#include "log.h"
#include "sys_info.h"

/*enum TYPE_NAMES
{
    tn_LIST,
    tn_LOGS
};*/


class LOGS_LIBRARY_EXPORT IConnector
{
protected:
    QByteArray bd;
public:
    virtual int connect() = 0;
    virtual int connect(QString host,quint16 port = 1616,QString user="",QString password="") = 0;
    virtual int send_cmd(QString cmd) = 0;
    virtual int is_connected() = 0;
    /*virtual int send_data(QVector<LOG> &log) =0;*/
    //virtual int send_data() = 0;
    virtual int send_data(QVector<LOG> &log) =0;
    //virtual int send_data(QMap<QString,QString> &si) =0;
    //virtual int send_data(QString &info) =0;
    //virtual int send_data(int &info) =0;
   // template <class T> int send_data(T log){};
    // template <class T> int send_data(QVector<T> log, TYPE_NAMES typeName){};
    virtual int close() = 0;
    virtual int decode_response(QString response) = 0;
};

class LOGS_LIBRARY_EXPORT DirectConnection : public QObject, public IConnector
{
    Q_OBJECT
private:
    QString server, password, username;
    int isConnected = -1;
    QTcpSocket *controlSocket,*dataSocket;
    quint16 controlPort = 1616, dataPort = 11718;
    QString serverNo, serverResponse;
public:
    //QThread *thread;

    DirectConnection();
    DirectConnection(QString host);
    DirectConnection(QString host,quint16 port);
    DirectConnection(QString host,quint16 port, QString user);
    DirectConnection(QString host,quint16 port, QString user,QString password);


    int is_connected() override {return isConnected;};
    int connect() override;
    int connect(QString host,quint16 port = 1616,QString user="",QString password="") override;
    int send_cmd(QString cmd) override;
    int decode_response(QString response) override;

    int close() override;

    void set_control_port(quint16 port) {controlPort=port;};
    void set_data_port(quint16 port) {dataPort=port;};

    virtual int send_data(QVector<LOG> &log) override;
    //virtual int send_data(QMap<QString,QString> &si) =0;
    //virtual int send_data(QString &info) =0;
    //virtual int send_data(int &info) =0;
    //template<class T> int send_data(T log);

    //   template<class T> int send_data(QVector<T> log, TYPE_NAMES typeName){};
};

/*
template <class T> int DirectConnection::send_data(T log)
{
    qDebug()<<"moze TUTAJ?";

    if(isConnected!=0)
    {
        return isConnected;
    }

    // controlSocket->write("SEND#logs");
    //controlSocket->waitForBytesWritten(30000);

    dataSocket = new QTcpSocket();
    dataSocket->connectToHost(this->server,11718);
    dataSocket->write(serverNo.toStdString().c_str());
    dataSocket->waitForBytesWritten();
    dataSocket->waitForReadyRead();
    serverResponse = dataSocket->readAll();

    if(serverResponse!="JUUPUI")
    {
        qDebug()<<serverResponse;
        return 1;
    }

    QDataStream ds(dataSocket);

    ds << log;

    //dataSocket->waitForBytesWritten();
    dataSocket->waitForReadyRead();
    serverResponse = dataSocket->readAll();

    if(serverResponse!="OK")
    {
        return 2;
        qDebug()<<"TEST"<<serverResponse;
    }

    dataSocket->disconnectFromHost();
    dataSocket->close();
    return 0;
}*/

#endif // ICONNECTOR_H
