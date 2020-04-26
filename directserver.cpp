#include "directserver.h"
#include <QCoreApplication>

DirectServer::DirectServer():
    QObject()
{
    logNum = 0;
    saveDir = QDir::homePath() +"\\";
    fileName = "client_log.xml";
    logs = nullptr;
    fe = FILE_EXT::NUMBERS;
    currentCMD="";
    controlPort=1616;
    dataPort=11718;

    control = new QTcpServer();
    control->listen(QHostAddress::Any,1616);

    data = new QTcpServer();
    data->listen(QHostAddress::Any,11718);

    QObject::connect(control,&QTcpServer::newConnection,this,&DirectServer::newControlConn);
    QObject::connect(data,&QTcpServer::newConnection,this,&DirectServer::newDataConn);

    fs = new XML();
}

void DirectServer::newControlConn()
{
    QTcpSocket *tmp = control->nextPendingConnection();
    clients.push_back(tmp);
    QObject::connect(tmp,&QTcpSocket::readyRead,this,&DirectServer::controlService);
    QObject::connect(tmp,&QTcpSocket::disconnected,this,&DirectServer::disconnectedSocket);
    tmp->write(QString::number(tmp->socketDescriptor()).toStdString().c_str());
    tmp->waitForBytesWritten();
}

void DirectServer::newDataConn()
{
    QTcpSocket *tmp = data->nextPendingConnection();
    tmp->waitForReadyRead(300000);
    QString tst = tmp->readAll();
    if(isAccepted(tst))
    {
        QObject::connect(tmp,&QTcpSocket::readyRead,this,&DirectServer::dataService);
        QObject::connect(tmp,&QTcpSocket::disconnected,this,&DirectServer::disconnectedSocket);
        tmp->write("JUUPUI");
        tmp->waitForBytesWritten();
    }
    else
    {
        tmp->write("Your connection wasn't accepted!Closing.");
        tmp->waitForBytesWritten();
        tmp->close();
    }
}

void DirectServer::controlService()
{
    QTcpSocket *tmp = qobject_cast<QTcpSocket*>(sender());
    QString bb = tmp->readAll();
    QList<QString> arg = bb.split("#");
    arg.removeAll("");
    qDebug()<<arg;
    qDebug()<<arg.count();
    if(arg[0]=="PASS")
    {
        if(arg.count()==2)
        {
            qDebug()<<tmp->peerPort();
            if(userTMP!="")
            {
                if(arg[1]==this->password)
                {
                    acceptedClients.push_back(tmp);
                    clients.removeAll(tmp);
                    tmp->write("Logged successfully");
                    tmp->waitForBytesWritten(30000);
                }
                else
                {
                    tmp->write("Wrong password");
                    tmp->waitForBytesWritten(30000);
                }

            }
            else
            {
                tmp->write("Username was not provided");
                tmp->waitForBytesWritten(30000);
            }
        }
    }

    if(arg[0]=="USER")
    {
        if(arg.count()==2)
        {
            if(arg[1]!=this->username)
            {
                userTMP = "";
                tmp->write("No username");
                tmp->waitForBytesWritten(30000);
            }
            else
            {
                userTMP = "jakis";
                tmp->write("Provide password to log in");
                tmp->waitForBytesWritten(30000);
            }
        }
    }

    if(arg[0]=="FNAME")
    {
        if(arg.count()==2)
        {
            qDebug()<<arg[1];
        }

    }
    if(arg[0]=="FEXT")
    {
        if(arg.count()==2)
        {
            qDebug()<<arg[1];
        }

    }
    if(arg[0]=="FDEF")
    {
        if(arg.count()==2)
        {
            qDebug()<<arg[1];
        }

    }
}

void DirectServer::disconnectedSocket()
{
    QTcpSocket *tmp = qobject_cast<QTcpSocket*>(sender());
    tmp->close();
    clients.removeAll(tmp);
    acceptedClients.removeAll(tmp);

    qDebug()<<"UDALO";
}

void DirectServer::dataService()
{
    QTcpSocket *tmp = qobject_cast<QTcpSocket*>(sender());

    QDataStream ds(tmp);
    QVector<LOG> tst;
    ds >> tst;
    this->logs = new LOGS(tst);

    tmp->write("OK");
    tmp->waitForBytesWritten();

    save();
    logNum++;
}

bool DirectServer::isAccepted(QString sck)
{
    for(auto it = acceptedClients.begin();it!=acceptedClients.end();it++)
    {
        if((*it)->socketDescriptor()==sck.toInt())
        {
            return true;
        }
    }
    return false;
}

int DirectServer::save()
{
    QString filePath = saveDir;
    QString fileExt = fileName.mid(fileName.length()-4);
    QString fileName2 = fileName.left(fileName.length()-4);

    if(fe==NUMBERS)
        fileName2 +="_"+QString::number(this->logNum);
    else
        fileName2 +="_"+(QDateTime::currentDateTime().toString("dd.MM.yyy_hh-mm-ss"));

    filePath +=fileName2+fileExt;

    logs->save(filePath,fs);

    return 0;
}
