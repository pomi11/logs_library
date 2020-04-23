#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>
#include "logs.h"

class LOGS_LIBRARY_EXPORT IConnector
{
protected:
    QByteArray bd;
public:
    virtual int connect() = 0;
    virtual int connect(QString host,quint16 port = 1616,QString user="",QString password="") = 0;
    virtual int send_cmd(QString cmd) = 0;
    virtual int send_data(QVector<LOG> &log) =0;
    virtual int send_data(LOGS &log) =0;
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


    int is_connected() const {return isConnected;};
    int connect() override;
    int connect(QString host,quint16 port = 1616,QString user="",QString password="") override;
    int send_cmd(QString cmd) override;
    int decode_response(QString response) override;
    int send_data(QVector<LOG> &log) override;
    int send_data(LOGS &log) override;
    int close() override;

    void set_control_port(quint16 port) {controlPort=port;};
    void set_data_port(quint16 port) {dataPort=port;};
};

#endif // ICONNECTOR_H
