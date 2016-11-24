#include <QHostAddress>
#include <QDateTime>
#include <QThread>
#include "TcpMsgClient.h"
#include "chatwindow.h"


TcpMsgClient::TcpMsgClient(QObject *parent):QTcpSocket(parent)
{
    consoleHandler=new ChatWindow(this);
    moveClientToThread();
}

//STEP 1
void TcpMsgClient::moveClientToThread()
{
    QThread* myThread = new QThread;
    connect(myThread,SIGNAL(started()),consoleHandler,SLOT(inputToVoid()));
    connect(this,SIGNAL(requestInputVoid()),consoleHandler,SLOT(inputToVoid()));
    connect(this,SIGNAL(requestInputServer()),consoleHandler,SLOT(inputToServer()));
    connect(this,SIGNAL(serverSet()),this,SLOT(getServer()));
    connect(this,SIGNAL(inputSet()),this,SLOT(fireTheMessage()));
    connect(this,SIGNAL(destroyed(QObject*)), myThread, SLOT(quit()));
    connect(myThread,SIGNAL(finished()),myThread,SLOT(deleteLater()));
    connect(this,SIGNAL(readyRead()), this, SLOT(readComingMessage()));
    this->moveToThread(myThread);
    myThread->start();
}
//STEP 2
void TcpMsgClient::setServerAdress(const QStringList& serAd)
{
    serverAdress=serAd;
    emit serverSet();
}
//STEP 3
void TcpMsgClient::getServer()
{
    this->connectToHost(QHostAddress(serverAdress.at(1)),
                             serverAdress.at(2).toInt());
    qDebug("Connecting...\n");
    if(this->waitForConnected(3000))
    {
        qDebug("Connection established!\n");
        connectionStatus=true;
        emit requestInputServer();
    }
    else
    {
        qDebug("Connection lost.\n");
        emit requestInputVoid();
    }
}
//STEP 4
void TcpMsgClient::setInput(const QString& inp)
{
        inputString=inp;
        emit inputSet();
}
//STEP 5
void TcpMsgClient::fireTheMessage()
{
    if(connectionStatus)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << inputString;
        this->write(block);
        emit requestInputServer();
    }
    else
    {
        connectionStatus=false;
        qDebug()<<"You have been disconnected...";
        emit requestInputVoid();
    }
}
//STEP 6-сам по себе шаг
void TcpMsgClient::readComingMessage()
{
    in.setDevice(this);
    in.setVersion(QDataStream::Qt_4_1);

    in.startTransaction();
    in >> messageReceived;

    if (!in.commitTransaction())
        return;
    qDebug()<<messageReceived;
}




