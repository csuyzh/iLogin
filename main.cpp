#define Q_OS_WIN

#ifdef Q_OS_WIN
#include "DesktopUI/mainui.h"
#include "singleapplication.h"
#endif

#ifdef Q_OS_LINUX
#include "DesktopUI/mainui.h"
#include "singleapplication.h"
#endif

#ifdef Q_OS_MACX
#include "DesktopUI/mainui.h"
#include "singleapplication.h"
#endif

#ifdef Q_OS_ANDROID
#include "MobileUI/mainui.h"
#include <QApplication>
#endif

#ifdef Q_OS_IOS
#include "MobileUI/mainui.h"
#include <QApplication>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    SingleApplication a(argc, argv);
//    if(a.isSingle()==false)
//        return 0;
#endif

#ifdef Q_OS_LINUX
    SingleApplication a(argc, argv);
    if(a.isSingle()==false)
        return 0;
#endif

#ifdef Q_OS_MACX
    SingleApplication a(argc, argv);
    if(a.isSingle()==false)
        return 0;
#endif

#ifdef Q_OS_ANDROID
    QApplication a(argc, argv);
#endif

#ifdef Q_OS_IOS
    QApplication a(argc, argv);
#endif
    a.setWindowIcon(QIcon("://img/icon.png"));
    qRegisterMetaType<UserInfo>("UserInfo");
    qRegisterMetaTypeStreamOperators<UserInfo>("UserInfo");
    MainUI w;
    return a.exec();
}
