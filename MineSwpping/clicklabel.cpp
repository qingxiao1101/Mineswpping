#include <QMouseEvent>
#include "clicklabel.h"
#include <QQueue>
#include <QEvent>
#include <QApplication>

class CustomEvent : public QEvent
{
public:
    explicit CustomEvent(Type myeventtype):QEvent(myeventtype){}
public:

private:
    int m_id;
};

void ClickLabel::Testsignal(void)
{
    qDebug()<<"signal ok";
}
bool Point::operator == (const Point& tmp)
{
  if( (this->x == tmp.x )&&(this->y == tmp.y))
      return true;
  else
      return false;
}
Point::Point()
{

}
Point::Point(int xx,int yy)
    :x(xx), y(yy)
{

}

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel(parent)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
    setFixedSize(30,30);
    setFrameStyle( QFrame::Panel | QFrame::Raised );
    setLineWidth( 4 );
    setMidLineWidth(1);
    this->SetAttribute(-1);
    this->SetArroundMine(0);
//    setText(tr("0"));
    connect(this, SIGNAL(leftclicked()), this, SLOT(LeftMausClick()));
    connect(this, SIGNAL(rightclicked()), this, SLOT(RightMausClick()));
    connect(this, SIGNAL(gameover()), this, SLOT(Testsignal()));
}

ClickLabel::ClickLabel(const QString &text, QWidget *parent) :
    QLabel(parent)
{
    setText(text);
}


void ClickLabel::SetAttribute(int a)
{
    attribute = a;
}
int ClickLabel::GetAttribute(void) const
{
    return attribute;
}
void ClickLabel::SetAddress(int x, int y)
{
    position.x = x;
    position.y = y;
}
Point  ClickLabel::GetAddress(void) const
{
    return position;
}
void ClickLabel::SetArroundMine(int am)
{
    arroundMine = am;
}
int ClickLabel::GetArroundMine(void) const
{
    return arroundMine;
}
void ClickLabel::SetFlag(bool f)
{
    flag = f;
}
bool ClickLabel::GetFlag(void)const
{
    return flag;
}
void ClickLabel::SetVisited(bool v)
{
    visited = v;
}
bool ClickLabel::GetVisited(void)const
{
    return visited;
}


// mark: protected:------------------------------------------------
void ClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit leftclicked();//(this);
}
void ClickLabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
        emit rightclicked();//(this);
}
void ClickLabel::enterEvent(QEvent * )
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::blue);
    setPalette(pa);
}
void ClickLabel::leaveEvent(QEvent *)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}

void ClickLabel::RightMausClick(void)
{
    if(this->GetFlag()==false&&this->GetVisited()==false)
    {
        this->SetFlag(true);
        this->setText(tr("F"));
        if(this->GetAttribute()==9)
        {
            ++sumFlag;
            if(sumFlag==sumMineCount)
            {
                CustomEvent * winn = new CustomEvent(GetGameEventType(gameWinn));
                QApplication::sendEvent((QObject*)mainwindow,winn);
            }
        }
    }
}

void ClickLabel::LeftMausClick(void)
{
    this->SetVisited(true);
    if(this->GetAttribute()==9)
    {//失败，游戏结束
        emit gameover();
        this->setText(tr("@"));
        CustomEvent *cut = new CustomEvent(GetGameEventType(gameOver));
        QApplication::sendEvent((QObject*)mainwindow,cut);
    }
    else
    {
        BfsResearch(minePointer,this->GetAddress());
    }
}
//=============================================================
void ClickLabel::BfsResearch(ClickLabel *cl,Point p)
{
    QQueue<Point> myQueue;
    Point tmp,adj;

    Level le = systemLevel;
    int x = p.x, y = p.y;
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //当前块雷个数为0， 广度搜索
    {
        (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        (le*y+x+cl)->setText(tr("0"));
        myQueue.push_front(p);
        while(!myQueue.empty())
        {
            tmp = myQueue.front();
            myQueue.pop_front();

            adj = Adjction(tmp);
            while(adj.x!=-1&&adj.y!=-1) //相邻元素不为空，执行
            {
                if((cl+adj.x+le*adj.y)->GetVisited()==false)
                {
                    (cl+adj.x+le*adj.y)->SetVisited(true);
                    (le*adj.y+adj.x+cl)->setFrameStyle( QFrame::Box | QFrame::Sunken );  //翻开 显示0
                    (le*adj.y+adj.x+cl)->setText(tr("0"));
                    myQueue.push_back(adj);
                }
                adj = Adjction(tmp);
            }
        }
    }
}
Point ClickLabel::Adjction(Point p) //返回-1，-1坐标表示没有相邻节点，否则返回坐标地址
{
    ClickLabel *cl = minePointer;
    Level le = systemLevel;
    int x = p.x, y = p.y;
    Point tmp;
    //左上
    if((p.x>=1)&&(p.y>=1)&&((cl+le*(y-1)+x-1)->GetVisited()==false)
            &&((cl+le*(y-1)+x-1)->GetArroundMine()==0)) {tmp.x=x-1;tmp.y=y-1;return tmp;}
    else if((p.x>=1)&&(p.y>=1)&&((cl+le*(y-1)+x-1)->GetVisited()==false)
            &&((cl+le*(y-1)+x-1)->GetArroundMine()!=0))
    {
        (cl+le*(y-1)+x-1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number((cl+le*(y-1)+x-1)->GetArroundMine());
        (cl+le*(y-1)+x-1)->setText(Minecount);
    }
    //左
    if((p.x>=1)&&((cl+le*y+x-1)->GetVisited()==false)
            &&((cl+le*y+x-1)->GetArroundMine()==0)) {tmp.x=x-1;tmp.y=y;return tmp;}
    else if((p.x>=1)&&((cl+le*y+x-1)->GetVisited()==false)
            &&((cl+le*y+x-1)->GetArroundMine()!=0))
    {
        (cl+le*y+x-1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number((cl+le*y+x-1)->GetArroundMine());
        (cl+le*y+x-1)->setText(Minecount);
    }
    //左下
    if((p.x>=1)&&(p.y+1<le)&&((cl+le*(y+1)+x-1)->GetVisited()==false)
            &&((cl+le*(y+1)+x-1)->GetArroundMine()==0)) {tmp.x=x-1;tmp.y=y+1;return tmp;}
    else if((p.x>=1)&&(p.y+1<le)&&((cl+le*(y+1)+x-1)->GetVisited()==false)
            &&((cl+le*(y+1)+x-1)->GetArroundMine()!=0))
    {
        (cl+le*(y+1)+x-1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number((cl+le*(y+1)+x-1)->GetArroundMine());
        (cl+le*(y+1)+x-1)->setText(Minecount);
    }
    //上
    if((p.y>=1)&&((cl+le*(y-1)+x)->GetVisited()==false)
           &&((cl+le*(y-1)+x)->GetArroundMine()==0) ){tmp.x=x;tmp.y=y-1;return tmp;}
    else if((p.y>=1)&&((cl+le*(y-1)+x)->GetVisited()==false)
            &&((cl+le*(y-1)+x)->GetArroundMine()!=0) )
    {
        (cl+le*(y-1)+x)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number((cl+le*(y-1)+x)->GetArroundMine());
        (cl+le*(y-1)+x)->setText(Minecount);
    }
    //下
     if((p.y+1<le)&&((cl+le*(y+1)+x)->GetVisited()==false)
             &&((cl+le*(y+1)+x)->GetArroundMine()==0)){tmp.x=x;tmp.y=y+1;return tmp;}
     else if((p.y+1<le)&&((cl+le*(y+1)+x)->GetVisited()==false)
             &&((cl+le*(y+1)+x)->GetArroundMine()!=0))
     {
         (cl+le*(y+1)+x)->setFrameStyle( QFrame::Box | QFrame::Sunken );
         QString Minecount = QString::number((cl+le*(y+1)+x)->GetArroundMine());
         (cl+le*(y+1)+x)->setText(Minecount);
     }
    //右上
     if((p.x+1<le)&&(p.y>=1)&&((cl+le*(y-1)+x+1)->GetVisited()==false)
             &&((cl+le*(y-1)+x+1)->GetArroundMine()==0)){tmp.x=x+1;tmp.y=y-1;return tmp;}
     else if((p.x+1<le)&&(p.y>=1)&&((cl+le*(y-1)+x+1)->GetVisited()==false)
             &&((cl+le*(y-1)+x+1)->GetArroundMine()!=0))
     {
         (cl+le*(y-1)+x+1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
         QString Minecount = QString::number((cl+le*(y-1)+x+1)->GetArroundMine());
         (cl+le*(y-1)+x+1)->setText(Minecount);
     }
    //右
     if((p.x+1<le)&&((cl+le*y+x+1)->GetVisited()==false)
             &&((cl+le*y+x+1)->GetArroundMine()==0)){tmp.x=x+1;tmp.y=y;return tmp;}
     else if((p.x+1<le)&&((cl+le*y+x+1)->GetVisited()==false)
             &&((cl+le*y+x+1)->GetArroundMine()!=0))
     {
         (cl+le*y+x+1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
         QString Minecount = QString::number((cl+le*y+x+1)->GetArroundMine());
         (cl+le*y+x+1)->setText(Minecount);
     }
    //右下
    if((p.x+1<le)&&(p.y+1<le)&&((cl+le*(y+1)+x+1)->GetVisited()==false)
            &&((cl+le*(y+1)+x+1)->GetArroundMine()==0)){tmp.x=x+1;tmp.y=y+1;return tmp;}
    else if((p.x+1<le)&&(p.y+1<le)&&((cl+le*(y+1)+x+1)->GetVisited()==false)
            &&((cl+le*(y+1)+x+1)->GetArroundMine()==0))
    {
        (cl+le*(y+1)+x+1)->setFrameStyle( QFrame::Box | QFrame::Sunken );
        QString Minecount = QString::number((cl+le*(y+1)+x+1)->GetArroundMine());
        (cl+le*(y+1)+x+1)->setText(Minecount);
    }
    else{tmp.x=-1;tmp.y=-1; return tmp;}
}












