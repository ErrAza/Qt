#include <QCoreApplication>
#include "myobject.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread cThread;
    MyObject cObject;

    cObject.DoSetup(cThread);
    cObject.moveToThread(&cThread);

    cThread.start();

    return a.exec();
}
