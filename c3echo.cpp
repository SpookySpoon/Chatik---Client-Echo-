#include <QHostAddress>
#include <QThread>

#include "c3echo.h"
#include "c3echosession.h"

C3Echo::C3Echo(const QStringList& someServerAdress, C3EchoSession* someHostSession, QObject *parent)
    : QObject(parent), serverAdress(someServerAdress), hostSession(someHostSession)
{
}

C3Echo::~C3Echo()
{
    delete tcpSocket;
}

void C3Echo::getServer()
{
    tcpSocket=new QTcpSocket();
    connect(tcpSocket,SIGNAL(readyRead()), this, SLOT(readComingMessage()));
    connect(this,SIGNAL(messageReady()), this, SLOT(fireTheMessage()));
    connect(tcpSocket,SIGNAL(disconnected()), this, SLOT(onDeletion()));
    connect(tcpSocket,SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(tcpSocket,SIGNAL(disconnected()), this->thread(), SLOT(quit()));
    tcpSocket->connectToHost(QHostAddress(serverAdress.at(1)),
                             serverAdress.at(2).toInt());
    qDebug("Connecting...\n");
    if(tcpSocket->waitForConnected(3000))
    {
        qDebug("Connection established!\n");
        readComingMessage();
        hostSession->connectionStatus=true;
    }
    else
    {
        qDebug("Connection lost.\n");
    }
}

void C3Echo::readComingMessage()
{
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_1);

    in.startTransaction();
    in >> messageReceived;

    if (!in.commitTransaction())
        return;
    qDebug()<<messageReceived;
}

void C3Echo::loadTheMessage(const QString& message)
{
    messageToSend=message;
    emit messageReady();
}

void C3Echo::fireTheMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << messageToSend;
    tcpSocket->write(block);
}

void C3Echo::onDeletion()
{
    hostSession->connectionStatus=false;
    qDebug()<<"Server is down, you will be thrown back into the void...";
}
