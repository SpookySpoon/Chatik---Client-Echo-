#include "chatclient.h"

ChatClient::ChatClient()
    :threadChat(), threadClient(), client(), cWindow(&client)
{
    qDebug()<<"To establish connection, type \"\\connect *adress*(space)*port number*\".";
    qDebug()<<"Type \"Quit\" to exit server.\n";
    qDebug()<<"Main func thread: "<<QThread::currentThreadId();
    QObject::connect(&threadClient,SIGNAL(started()),&cWindow,SLOT(inputToVoid()));
    QObject::connect(&client,SIGNAL(requestInputVoid()),&cWindow,SLOT(inputToVoid()));
    QObject::connect(&client,SIGNAL(requestInputServer()),&cWindow,SLOT(inputToServer()));

    QObject::connect(&cWindow,SIGNAL(sendServerAdress(QString)),&client,SLOT(getServer(QString)));
    QObject::connect(&cWindow,SIGNAL(sendServerInput(QString)),&client,SLOT(fireTheMessage(QString)));
    QObject::connect(&cWindow,SIGNAL(initDisconnect()),&client,SLOT(quitConnection()));
    QObject::connect(&client,SIGNAL(disconnected()),&client,SLOT(uponDistonnect()));


    QObject::connect(&client,SIGNAL(destroyed(QObject*)), &threadClient, SLOT(quit()));
    QObject::connect(&threadClient,SIGNAL(finished()),&threadClient,SLOT(deleteLater()));
    QObject::connect(&client,SIGNAL(readyRead()), &client, SLOT(readComingMessage()));
    client.moveToThread(&threadClient);
    cWindow.moveToThread(&threadChat);
    threadChat.start();
    threadClient.start();
}
