#include <QHostAddress>
#include <QDateTime>
#include <QThread>
#include "tcpmsgclient.h"
#include "chatwindow.h"
#include "messageformat.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

TcpMsgClient::TcpMsgClient(QObject *parent):QTcpSocket(parent)
{
}

//STEP 3
void TcpMsgClient::getServer(const QString& serAdress)
{
    QStringList splitAdress = serAdress.split(" ");
    this->connectToHost(QHostAddress(splitAdress.at(1)),
                             splitAdress.at(2).toInt());
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

//STEP 5
void TcpMsgClient::fireTheMessage(const QString& inp)
{
    //        QByteArray block;                                         BEFORE
    //        QDataStream out(&block, QIODevice::WriteOnly);            BEFORE
    //        out << inp;                                               BEFORE
    //        this->write(block);                                       BEFORE
    if(connectionStatus)
    {
        chatMes::hello protoMessage;//                              new protobuf
        {
            protoMessage.set_data(inp.toLatin1().data());//       new protobuf
        }
        int siz = protoMessage.ByteSize();//                              new protobuf
        char *pkt = new char [siz];//                              new protobuf
        google::protobuf::io::ArrayOutputStream aos(pkt,siz);//                              new protobuf
        google::protobuf::io::CodedOutputStream* coded_output = new google::protobuf::io::CodedOutputStream(&aos);//                              new protobuf
        coded_output->WriteVarint32(siz);//                              new protobuf
        protoMessage.SerializeToCodedStream(coded_output);//                              new protobuf
        this->write(pkt);
        emit requestInputServer();
    }
    else
    {
        qDebug()<<"Sending failed. Redirecting you to the void";
        emit requestInputVoid();
    }
}

//STEP 6-сам по себе шаг
void TcpMsgClient::readComingMessage()
{
    chatMes::hello protoMessage;//       new protobuf
    google::protobuf::uint32 size;//       new protobuf
    QByteArray incomingMessage=this->readAll();//       new protobuf
    google::protobuf::io::ArrayInputStream ais(incomingMessage,incomingMessage.count());//       new protobuf
    google::protobuf::io::CodedInputStream coded_input(&ais);//       new protobuf
    coded_input.ReadVarint32(&size);//       new protobuf
    protoMessage.ParseFromCodedStream(&coded_input);//       new protobuf
    QString result = QString::fromStdString(protoMessage.DebugString());//       new protobuf
    qDebug()<<result;//       new protobuf


//    QString messageReceived;
//    in.setDevice(this);
//    in >> messageReceived;
//    qDebug()<<messageReceived;
}

void TcpMsgClient::quitConnection()
{
    connectionStatus=false;
    qDebug()<<"Disconnecting...";
    this->disconnectFromHost();
}

void TcpMsgClient::uponDistonnect()
{
    if(!connectionStatus)
    {
        qDebug()<<"You have successfully disconnected...";
        emit requestInputVoid();//этот сигнал не стоит в конце файла, потому что если соединение упало, а connectionStatus = true
        //это только если сервер упал. В таком случае я отправлю сообщение, оно не пройдет и я попаду на строчку 46
    }
    else
    {
        connectionStatus=false;
        qDebug()<<"You have been disconnected...";
    }
}

template<typename T>
QByteArray protoToByteArray(const T& proto)
{
 if (!proto.IsInitialized()) {
  return QByteArray();
 }
 QByteArray outBA;
 outBA.resize(proto.ByteSize());
 proto.SerializeToArray(outBA.data(), outBA.size()+1);
 return outBA;
}



