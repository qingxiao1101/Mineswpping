#include "mainwindow.h"
#include <QApplication>
#include "publicdate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,Level3);
    w.show();

    return a.exec();
}
