#pragma once
#include <QObject>
#include <QTcpSocket>


class TcpMsgClient : public QTcpSocket
{
    Q_OBJECT
    bool connectionStatus=false;
public:
    explicit TcpMsgClient(QObject *parent = nullptr);
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
