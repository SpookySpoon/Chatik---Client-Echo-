#include <QApplication>
#include <QTextStream>
#include "c3echosession.h"

int main(int argc, char *argv[])
{
    QTextStream cin(stdin);
    QTextStream cout(stdout);
    QApplication app(argc, argv);
    C3EchoSession* newSession;
    QString myInput;
    QStringList connectCheck;
    cout<<"To establish connection, type \"\\connect *adress*(space)*port number*\"."<<endl;
    cout<<"Type \"Quit\" to exit server.\n"<<endl;

    while (1)
    {
        printf("<Enter a server adress>");
        myInput=cin.readLine();
        connectCheck=myInput.split(" ");

        if (connectCheck.at(0)=="\\connect"&&connectCheck.count()==3)
        {
            newSession=new C3EchoSession(connectCheck);
        }
    }
    return app.exec();
}
