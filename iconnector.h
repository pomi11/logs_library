#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "logs_library_global.h"
#include <QtNetwork/QtNetwork>

class LOGS_LIBRARY_EXPORT IConnector
{
public:
    virtual int connect() = 0;
    virtual int connect(QString host,QString user="",QString password="") = 0;
    virtual int send() = 0;
    virtual int close() = 0;
};

/*class DirectConnection : public QObject, public IConnector
{
    Q_OBJECT
private:
    bool isConnected = false;
    QTcpSocket *controlSocket,*networkSocket;
public:
    QThread *thread;

    DirectConnection();
    DirectConnection(QString host);
    DirectConnection(QString host,QString user);
    DirectConnection(QString host,QString user,QString password);


    bool is_connected() const {return isConnected;};
    int connect() override;
    int connect(QString host,QString user="",QString password="") override;
    void send_command(QString command);
    int close() override;
};*/

#endif // ICONNECTOR_H
