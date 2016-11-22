#include <QTextStream>
#include <QDateTime>
#include "c3echo.h"
#include "c3echosession.h"

C3EchoSession::C3EchoSession(const QStringList& someServerAdress, QObject *parent)
    :QObject(parent),serverAdress(someServerAdress)
{
    connect(this,SIGNAL(created()),this,SLOT(addClient()));
    emit created();
}


void C3EchoSession::addClient()
{
    client3=new C3Echo(serverAdress,this);
    myThread = new QThread;
    connect(myThread,SIGNAL(started()),client3,SLOT(getServer()));
    connect(myThread,SIGNAL(finished()),myThread,SLOT(deleteLater()));
    connect(myThread,SIGNAL(finished()),this,SLOT(deleteLater()));
    client3->moveToThread(myThread);
    myThread->start();
    QTextStream txtS(stdin);
    while(quitString!="Quit")
    {
        quitString=txtS.readLine();
        if(quitString!="Quit"&&connectionStatus)
        {
           client3->loadTheMessage(QString("%1[::]%2")
                .arg(quitString)
                .arg(QDateTime::currentDateTimeUtc().addSecs(3600*3).toString("hh:mm:ss")));
        }
        else
        {
            break;
        }
    }
}

