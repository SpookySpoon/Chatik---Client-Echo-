#include <QDateTime>
#include "chatwindow.h"
#include "TcpMsgClient.h"


//этот класс для работы с консолью надо бы запихать в отдельный тред, а то он так вместе с Main() делит один тред
//но я для простоты не стал этого делать, т.к. тут здесь таки придется создавать фабричный класс ( в случае с TcpSocket было не обязательно)
ChatWindow::ChatWindow(TcpMsgClient* someClient, QObject *parent)
    :QObject(parent),tcpClient(someClient)
{}

void ChatWindow::inputToVoid()
{
    printf("<Enter a server adress>");
    QTextStream txtS(stdin);
    QString input=txtS.readLine();
    QStringList serverAdress=input.split(" ");
    if(serverAdress.at(0)=="\\connect"&&serverAdress.count()==3)
    {
        tcpClient->setServerAdress(serverAdress);
    }
    else
    {
        inputToVoid();//Если ввели что то левое то будет гонять себя по кругу
    }
}

void ChatWindow::inputToServer()
{
    QTextStream txtS(stdin);
    QString input=txtS.readLine();
    if(input!="Quit")
    {
        tcpClient->setInput(QString("%1[::]%2")
        .arg(input)
        .arg(QDateTime::currentDateTimeUtc().addSecs(3600*3).toString("hh:mm:ss")));//К сообщению добавляется время отправки
        //взято глобальное время и доведено до московского. Не стал закапываться с конвертацией локального времени между пользователями
    }
    else
    {
        qDebug()<<"You have quit the server.";
        inputToVoid();
    }
}
