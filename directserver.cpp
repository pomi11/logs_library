#include "directserver.h"
#include <QCoreApplication>

DirectServer::DirectServer():
    QObject()
{
   control = new QTcpServer();
   control->listen(QHostAddress::Any,1616);

   data = new QTcpServer();
   data->listen(QHostAddress::Any,11718);

   QObject::connect(control,&QTcpServer::newConnection,this,&DirectServer::newControlConn);
   QObject::connect(data,&QTcpServer::newConnection,this,&DirectServer::newDataConn);
  // listen(QHostAddress::Any,1617);
   //QObject::connect(this,&DirectServer::go,this,&DirectServer::loop);
}

void DirectServer::newControlConn()
{
        QTcpSocket *tmp = control->nextPendingConnection();
        qDebug()<<tmp->peerPort();
        clients.push_back(tmp);
        QObject::connect(tmp,&QTcpSocket::readyRead,this,&DirectServer::controlService);
        //QObject::connect(tmp,&QTcpSocket::writ,this,&DirectServer::clientService);
}

void DirectServer::newDataConn()
{
        QTcpSocket *tmp = control->nextPendingConnection();
        qDebug()<<tmp->peerPort();
        clients.push_back(tmp);
        QObject::connect(tmp,&QTcpSocket::readyRead,this,&DirectServer::dataService);
        //QObject::connect(tmp,&QTcpSocket::writ,this,&DirectServer::clientService);
}

void DirectServer::controlService()
{
    QTcpSocket *tmp = qobject_cast<QTcpSocket*>(sender());
    QString bb = tmp->readAll();

    if(bb.indexOf("PASS"))
    {

    }

    QThread::sleep(6);
    tmp->write("accept");
    tmp->waitForBytesWritten(20000);
}

void DirectServer::dataService()
{
    QTcpSocket *tmp = qobject_cast<QTcpSocket*>(sender());
    QString bb = tmp->readAll();

    if(bb.indexOf("PASS"))
    {

    }

    QThread::sleep(6);
    tmp->write("accept");
    tmp->waitForBytesWritten(20000);
}

int DirectServer::save()
{
    QString filePath = saveDir;
    QString fileExt = fileName.mid(fileName.length()-4);
    QString fileName2 = fileName.left(fileName.length()-4);

    if(fe==NUMBERS)
        fileName2 +="_"+QString::number(this->logNum);
    else
        fileName2 +="_"+QString::number(this->logNum);

    filePath +=fileName2+fileExt;

    logs->save(filePath);

    return 0;
}

/*
DirectThread::DirectThread(int socketDescriptor, const QString &fortune, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), text(fortune)
{
}

void DirectThread::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::ReadOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out >> text;

    qDebug()<<text;
    text = tcpSocket.readAll();
    qDebug()<<text;
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
*/
