#include "mainwindow.h"
#include <QApplication>
#include "publicdate.h"
#include "corealgorithem.h"
#include "gameevent.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,Level3);
    mainwindow = &w;
    w.show();

    return a.exec();
}

