#pragma once
#include <QObject>

class TcpMsgClient;


class ChatWindow : public QObject
{
    Q_OBJECT
public:
    ChatWindow(TcpMsgClient* someClient= nullptr, QObject *parent = nullptr);
public slots:
    void inputToVoid();
    void inputToServer();
private:
    TcpMsgClient* tcpClient= nullptr;
};

