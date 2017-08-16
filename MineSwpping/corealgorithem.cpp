#include "corealgorithem.h"
#include <QTime>
#include <QDebug>
#include "mainwidget.h"
#include "clicklabel.h"
#include "publicdate.h"

void fun(Point *a, int limit,int count)
{
    int i,n=0;
    Point t;
    t.x=qrand()%limit;
    t.y=qrand()%limit;
    while(n<count)
    {
        for (i=0;i<n;i++)
            if (t==a[i]) break;
        if (i==n)
        {
            a[n]=t;
            n++;
        }
        t.x=qrand()%limit;
        t.y=qrand()%limit;
     }
}

Point * SetMineRand(Level le)
{
    int countMine = sumMineCount; //设置雷的个数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    Point *p = new Point[countMine];
    fun(p,le,countMine);
//    qDebug()<<p[0].x<<p[0].y;
//    qDebug()<<p[1].x<<p[1].y;
//    qDebug()<<p[2].x<<p[2].y;
//    qDebug()<<p[3].x<<p[3].y;
//    qDebug()<<p[4].x<<p[4].y;
//    qDebug()<<p[5].x<<p[5].y;
//    qDebug()<<p[6].x<<p[6].y;
//    qDebug()<<p[7].x<<p[7].y;
//    qDebug()<<p[8].x<<p[8].y;
//    qDebug()<<p[9].x<<p[9].y;
//    qDebug()<<p[10].x<<p[10].y;
//    qDebug()<<p[11].x<<p[11].y;
    return p;
}

void MineLayout(ClickLabel * cl,Level le)
{
    Point * p=SetMineRand(le);
    for(int i=0;i<sumMineCount;i++)  //le
    {
        int x,y;
        x = (p+i)->x;
        y = (p+i)->y;
//        (le*y+x+cl)->SetAddress();
        (le*y+x+cl)->SetAttribute(9);
        qDebug()<<(le*y+x+cl)->GetAddress().x<<" "<<(le*y+x+cl)->GetAddress().y;
    }
}

int MineCounterOneCircuit(ClickLabel * cl, Point p,Level le)
{
    int Minenum = 0;
    int x = p.x, y = p.y;
    if((p.x>=1)&&(p.y>=1)&&((le*(y-1)+x-1+cl)->GetAttribute()==9)) Minenum++;
    if((p.x>=1)&&((le*y+x-1+cl)->GetAttribute()==9)) Minenum++;
    if((p.x>=1)&&(p.y+1<le)&&((le*(y+1)+x-1+cl)->GetAttribute()==9)) Minenum++;
    if((p.y>=1)&&((le*(y-1)+x+cl)->GetAttribute()==9)) Minenum++;
    if((p.y+1<le)&&((le*(y+1)+x+cl)->GetAttribute()==9)) Minenum++;
    if((p.x+1<le)&&(p.y>=1)&&((le*(y-1)+x+1+cl)->GetAttribute()==9)) Minenum++;
    if((p.x+1<le)&&((le*y+x+1+cl)->GetAttribute()==9))  Minenum++;
    if((p.x+1<le)&&(p.y+1<le)&&((le*(y+1)+x+1+cl)->GetAttribute()==9))  Minenum++;
    return Minenum;
}

