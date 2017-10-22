#include "singleapplication.h"
#include <QLocalSocket>
#include <QLocalServer>

SingleApplication::SingleApplication(int &argc, char *argv[]) :
    QApplication(argc,argv),
    hasInstance(false)
{
    QLocalSocket socket;
    socket.connectToServer("iLogin");
    if(socket.waitForConnected(500)) { //如果能够连接得上的话，将参数发送到服务器，然后退出
         hasInstance = true;
        return;
     }
     //运行到这里，说明没有实例在运行，那么创建服务器。
     localServer = new QLocalServer(this);
     localServer->listen("iLogin");
}

bool SingleApplication::isSingle()const{
    return !hasInstance;
}
