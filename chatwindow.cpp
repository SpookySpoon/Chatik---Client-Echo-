#include <QThread>
#include "chatwindow.h"
#include "tcpmsgclient.h"

ChatWindow::ChatWindow(TcpMsgClient* someClient, QObject *parent)
    :QObject(parent),tcpClient(someClient)
{}
QTextStream txtS(stdin);
void ChatWindow::inputToVoid()
{
    printf("<Enter a server adress>");
    QString input=txtS.readLine();
    QStringList serverAdress=input.split(" ");
    if(serverAdress.at(0)=="\\connect"&&serverAdress.count()==3)
    {
        emit sendServerAdress(input);
    }
    else
    {
        inputToVoid();//Если ввели что то левое то будет гонять себя по кругу
    }
}

void ChatWindow::inputToServer()
{
    QString input=txtS.readLine();
    if(input!="Quit")
    {
        if(input.count()>0)
        {
            emit sendServerInput(input);
        }
        else
        {
            inputToServer();
        }
    }
    else
    {
        emit initDisconnect();
    }
}
