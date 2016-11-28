#pragma once
#include <QThread>
#include "tcpmsgclient.h"
#include "chatwindow.h"


class ChatClient
{
    QThread threadChat;
    QThread threadClient;
    TcpMsgClient client;
    ChatWindow cWindow;
public:
    ChatClient();   
};

