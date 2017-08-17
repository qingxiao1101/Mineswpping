#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#include <QApplication>
#include <QCoreApplication>
#include <QEvent>
#include <QObject>
#include <QDebug>

class MyEvent:public QEvent
{
public:
    MyEvent(Type myeventtype):QEvent(myeventtype){}
};

class MySender:public QCoreApplication
{

public:
    MySender(int argc,char *argv[]):QCoreApplication(argc,argv){}
    bool notify(QObject *receiver, QEvent *event);
};

class MyArmy: public QObject
{
public:
   void MyEventHandler(QEvent *event);//自定义事件函数
   bool event(QEvent *event);
};

class MyWatcher: public QObject
{
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

int MainGameEvent(int argc, char *argv[]);

#endif // GAMEEVENT_H
