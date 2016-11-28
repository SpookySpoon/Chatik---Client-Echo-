#include <QApplication>
#include "chatclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChatClient newClient;
    return app.exec();
}
