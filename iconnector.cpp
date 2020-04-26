#include "iconnector.h"

DirectConnection::DirectConnection()
{
    controlSocket = new QTcpSocket();
    dataSocket = new QTcpSocket();

    isConnected = -1;
    controlPort = 1616;
    dataPort = 11718;
}

DirectConnection::DirectConnection(QString host)
    :DirectConnection()
{
    this->server=host;
}

DirectConnection::DirectConnection(QString host,quint16 port)
    :DirectConnection(host)
{
    this->controlPort=port;
}

DirectConnection::DirectConnection(QString host,quint16 port,QString user)
    :DirectConnection(host,port)
{
    this->username=user;

}

DirectConnection::DirectConnection(QString host,quint16 port,QString user,QString password)
    :DirectConnection(host,port,user)
{
    this->password=password;
}

int DirectConnection::connect()
{
    if(server=="")
        return -2;
    controlSocket->connectToHost(server,controlPort);
    qDebug()<<controlSocket->waitForConnected(2000);
    qDebug()<<controlSocket->waitForReadyRead(30000);
    serverNo = controlSocket->readAll();
    QString cmd;

    if(username!="")
    {
        cmd ="USER#"+username;
        send_cmd(cmd);
        if(password!="")
        {
            cmd ="PASS#"+password;
            send_cmd(cmd);
        }
    }

    qDebug()<<serverResponse;

    isConnected = decode_response(serverResponse);
    return isConnected;
}

int DirectConnection::connect(QString host,quint16 port,QString user,QString password)
{
    this->server=host;
    this->controlPort=port;
    this->username=user;
    this->password=password;

    return this->connect();
}

void DirectConnection::send_cmd(QString cmd)
{
    controlSocket->write(cmd.toStdString().c_str());
    controlSocket->waitForBytesWritten(30000);
    controlSocket->waitForReadyRead();
    serverResponse = controlSocket->readAll();

   // return 0;
}

int DirectConnection::decode_response(QString response)
{
    if(response=="Logged successfully")
        return 0;

    if(response=="No username")
        return 1;

    if(response=="Provide password to log in")
        return 2;

    if(response=="Wrong password")
        return 3;

    if(response=="Username was not provided")
        return 4;

    return -1;
}

int DirectConnection::send_data(QVector<LOG> &log)
{
    if(isConnected!=0)
    {
        return isConnected;
    }

    dataSocket = new QTcpSocket();
    dataSocket->connectToHost(this->server,this->dataPort);
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
}

void DirectConnection::close()
{
    controlSocket->disconnectFromHost();
    controlSocket->close();
}
