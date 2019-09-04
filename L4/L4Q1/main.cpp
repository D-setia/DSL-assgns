#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFile file("L4_P1_input.csv");
    QStringList wordMeaning;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }

    while(!file.atEnd()){
        QString ipline = file.readLine();
        QStringList l = ipline.split(';');
        w.insert(l.at(0), l.at(1));
    }

    w.show();
    return a.exec();
}
