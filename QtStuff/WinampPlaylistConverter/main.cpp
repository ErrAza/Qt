#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile mFile("c://winampplaylist2k14.txt");
    QFile readFile(QString str);

    QTextStream in(&readFile);
    QTextStream out(&mFile);

    QString mText = in.readAll();
    mText.replace("E:", "D:");
    out << mText;


    return a.exec();
}
