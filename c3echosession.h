#pragma once
#include <QObject>
#include <QThread>

class C3Echo;

class C3EchoSession: public QObject
{
    Q_OBJECT
public:
    C3EchoSession(const QStringList& someServerAdress, QObject *parent = Q_NULLPTR);
    bool connectionStatus=false;
private:
    QThread* myThread=Q_NULLPTR;
    C3Echo* client3=Q_NULLPTR;
    const QStringList& serverAdress;
    QString quitString="";

private slots:
    void addClient();
signals:
    void created();
};
