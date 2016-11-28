#pragma once
#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QTcpSocket>


class ChatWindow;

class TcpMsgClient : public QTcpSocket
{
    Q_OBJECT
    bool connectionStatus=false;
    QDataStream in;

public:
    explicit TcpMsgClient(QObject *parent = nullptr);
    template<typename T>
    QByteArray protoToByteArray(const T& proto);
public slots:
    void getServer(const QString&);
    void fireTheMessage(const QString&);
    void readComingMessage();
    void quitConnection();
    void uponDistonnect();
signals:
    void requestInputVoid();
    void requestInputServer();

};
