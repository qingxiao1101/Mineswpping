
#include "gameevent.h"
//声明、定义、注册自定义事件类型，事件ID为自定义事件ID起点QEvent::User +100=1100
 static const QEvent::Type MyEventType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);

bool MySender::notify(QObject *receiver, QEvent *event)
{
    if(event->type() == MyEventType)
    {
        qDebug()<<"MyEventType is coming!";
    }
    return QCoreApplication::notify(receiver,event);
}

void MyArmy::MyEventHandler(QEvent *event)
{
    qDebug()<<"The event is being handled!";
    event->accept();
}

bool MyArmy::event(QEvent *event)
{
    if(event->type() == MyEventType)
    {
        qDebug()<<"event() is dispathing MyEvent";
        MyEventHandler(event);//调用事件处理函数
        if((MyEvent*)event->isAccepted())
        {
            qDebug()<<"The event has been handled!";
            return true;
        }
    }
    return QObject::event(event);
}

bool MyWatcher::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == MyEventType)
    {
        qDebug()<<"I don't wanna filter MyEventType";
        return false;
    }
    return QObject::eventFilter(watched,event);
}

int MainGameEvent(int argc, char *argv[])
{
    MySender mySender(argc,argv);
    MyArmy myArmy;
    MyWatcher myWatcher;
    myArmy.installEventFilter(&myWatcher);//安装事件过滤器
    MyEvent myEvent(MyEventType);
    mySender.sendEvent(&myArmy,&myEvent);
    return mySender.exec();
}
