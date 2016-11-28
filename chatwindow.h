#pragma once
#include <QObject>

class TcpMsgClient;

class ChatWindow : public QObject
{
    Q_OBJECT
    TcpMsgClient* tcpClient= nullptr;
public:
    ChatWindow(TcpMsgClient* someClient= nullptr, QObject *parent = nullptr);
public slots:
    void inputToVoid();
    void inputToServer();
signals:
    void sendServerAdress(const QString&);
    void sendServerInput(const QString&);
    void initDisconnect();

};

