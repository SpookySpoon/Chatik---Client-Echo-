#include <QCoreApplication>
#include <QTextStream>
#include <QThread>
#include "TcpMsgClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qDebug()<<"To establish connection, type \"\\connect *adress*(space)*port number*\".";
    qDebug()<<"Type \"Quit\" to exit server.\n";
    new TcpMsgClient;

    return app.exec();
}
