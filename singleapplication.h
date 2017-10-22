#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>

class QLocalServer;

class SingleApplication : public QApplication
{
public:
    explicit SingleApplication(int &argc, char *argv[]);
    bool isSingle()const;
private:
    QLocalServer *localServer;
    bool hasInstance;
};

#endif // SINGLEAPPLICATION_H
