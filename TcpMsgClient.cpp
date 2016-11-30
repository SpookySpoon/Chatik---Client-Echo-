#include <QHostAddress>
#include <QDateTime>
#include <QTextStream>
#include "tcpmsgclient.h"
#include "protobytes.h"
#include "messageformat.pb.h"

TcpMsgClient::TcpMsgClient(QObject *parent):QTcpSocket(parent)
{
}
QTextStream cout(stdout);

void TcpMsgClient::getServer(const QString& serAdress)
{
    QStringList splitAdress = serAdress.split(" ");
    this->connectToHost(QHostAddress(splitAdress.at(1)),
                             splitAdress.at(2).toInt());
    cout<<"Connecting...\n"<<endl;
    if(this->waitForConnected(3000))
    {
        cout<<"Connection established!\n"<<endl;
        connectionStatus=true;
        emit requestInputServer();
    }
    else
    {
        cout<<"Connection lost.\n"<<endl;
        emit requestInputVoid();
    }
}

void TcpMsgClient::fireTheMessage(const QString& inp)
{
    if(connectionStatus)
    {
        chatMes::hello protoMessage;
        {
            protoMessage.set_datetime(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()/1000);
            protoMessage.set_mestext(inp.toStdString());
            protoMessage.set_nickname("");
        }
        QByteArray exportBytes=ProtoBytes<chatMes::hello>::protoToByteArray(protoMessage);
        this->write(exportBytes);
        emit requestInputServer();
    }
    else
    {
        cout<<"Sending failed. Redirecting you to the void"<<endl;
        emit requestInputVoid();
    }
}

void TcpMsgClient::readComingMessage()
{
    chatMes::hello protoMessage;
    QByteArray incomingMessage=this->readAll();
    protoMessage=ProtoBytes<chatMes::hello>::protoFromByteArray(incomingMessage);
    QString msgTime=QDateTime::fromMSecsSinceEpoch(protoMessage.datetime()*1000).toString("hh:mm:ss");
    QString result = QString("<(%1)%2>: %3").arg(msgTime).arg(QString::fromStdString(protoMessage.nickname())).arg(QString::fromStdString(protoMessage.mestext()));
    cout<<result<<endl;
}

void TcpMsgClient::quitConnection()
{
    connectionStatus=false;
    cout<<"Disconnecting..."<<endl;
    this->disconnectFromHost();
}

void TcpMsgClient::uponDistonnect()
{
    if(!connectionStatus)
    {
        cout<<"You have successfully disconnected..."<<endl;
        emit requestInputVoid();
    }
    else
    {
        connectionStatus=false;
        cout<<"You have been disconnected..."<<endl;
    }
}



