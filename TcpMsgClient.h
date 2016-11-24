#pragma once
#include <QObject>
#include <QDataStream>
#include <QTcpSocket>


class ChatWindow;

class TcpMsgClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpMsgClient(QObject *parent = nullptr);
    void setServerAdress(const QStringList& message);
    void setInput(const QString& message);
public slots:
    void getServer();
    void readComingMessage();
    void fireTheMessage();
signals:
    void requestInputVoid();
    void requestInputServer();
    void serverSet();
    void inputSet();
private:

    void moveClientToThread();
    ChatWindow* consoleHandler= nullptr;
    QString inputString;
    bool connectionStatus=false;
    QString messageReceived;
    QDataStream in;
    QStringList serverAdress;
};
