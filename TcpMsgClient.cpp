#include <QHostAddress>
#include <QDateTime>
#include <QTextStream>
#include "tcpmsgclient.h"
#include "messageformat.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

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
        int siz = protoMessage.ByteSize()+1;
        char *pkt = new char [siz];
        google::protobuf::io::ArrayOutputStream aos(pkt,siz);
        google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);
        coded_output->WriteVarint32(siz);
        protoMessage.SerializeToCodedStream(coded_output);
        this->write(pkt);
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
    google::protobuf::uint32 size;
    QByteArray incomingMessage=this->readAll();
    google::protobuf::io::ArrayInputStream ais(incomingMessage,incomingMessage.count());
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);
    protoMessage.ParseFromCodedStream(&coded_input);
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



