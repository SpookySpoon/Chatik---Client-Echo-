#pragma once
#include <QObject>
#include <QDataStream>
#include <QTcpSocket>

class C3EchoSession;

class C3Echo : public QObject
{
    Q_OBJECT
public:
    explicit C3Echo(const QStringList& someServerAdress, C3EchoSession* someHostSession,  QObject *parent = Q_NULLPTR);
    ~C3Echo();
    void loadTheMessage(const QString& message);
public slots:
    void getServer();
    void readComingMessage();
    void fireTheMessage();
    void onDeletion();
signals:
    void messageReady();
    void readyRead();
private:
    QString messageReceived, messageToSend;
    QString nickName="<Anonymous>";
    QDataStream in;
    C3EchoSession* hostSession=0;
    QTcpSocket *tcpSocket=0;
    const QStringList& serverAdress;
};
