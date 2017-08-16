#include <QMouseEvent>
#include "clicklabel.h"

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
void ClickLabel::SetOpenFlag(bool of)
{
    openFlag = of;
}
bool ClickLabel::GetOpenFlag(void)const
{
    return openFlag;
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
    setFrameStyle( QFrame::Panel | QFrame::Plain );
    this->SetFlag(true);
    if(GetAttribute()==9)
    {
        /*youxijieshu*/
        this->setText(tr("n"));
    }
    else
    {
//        QString attributestr = QString::number(GetAttribute());
        this->setText(tr("m"));
    }
}
void ClickLabel::LeftMausClick(void)
{
    this->SetOpenFlag(true);
    if(this->GetAttribute()==9)
        this->setText(tr("Bo"));
    else
    {
        MinerecursionLeftUp(minePointer,this->GetAddress());
        MinerecursionRightDown(minePointer,this->GetAddress());
    }
}
//=============================================================

void ClickLabel::Minerecursion(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
//        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(tr("0"));
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
        QString Minecount = QString::number(0);
         (le*y+x+cl)->setText(Minecount);

          if((p.x>=1)&&(p.y>=1))
          {
              MinerecursionLeftUp(cl,(le*(y-1)+x-1+cl)->GetAddress());
          }

          if((p.x>=1))
          {
              MinerecursionLeft(cl,(le*y+x-1+cl)->GetAddress());
//              MinerecursionLeftUp(cl,(le*y+x-1+cl)->GetAddress());
          }

          if((p.x>=1)&&(p.y+1<le))
          {
              MinerecursionLeftDown(cl,(le*(y+1)+x-1+cl)->GetAddress());
//              MinerecursionLeftUp(cl,(le*(y+1)+x-1+cl)->GetAddress());
          }

          if((p.y>=1))
          {
              MinerecursionUp(cl,(le*(y-1)+x+cl)->GetAddress());
//              MinerecursionLeftUp(cl,(le*(y-1)+x+cl)->GetAddress());
          }

/****************************************************************/

          if((p.y+1<le))
          {
              MinerecursionDown(cl,(le*(y+1)+x+cl)->GetAddress());
          }

          if((p.x+1<le))
          {
              MinerecursionRightUp(cl,(le*(y-1)+x+1+cl)->GetAddress());
          }

          if(p.x+1<le)
          {
              MinerecursionRight(cl,(le*y+x+1+cl)->GetAddress());
          }

          if((p.x+1<le)&&(p.y+1<le))
          {
              MinerecursionRightDown(cl,(le*(y+1)+x+1+cl)->GetAddress());
          }
    }
}

/**********************************************************************************************/

void  ClickLabel::MinerecursionLeftUp(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
          if((p.x>=1)&&(p.y>=1)) MinerecursionLeftUp(cl,(le*(y-1)+x-1+cl)->GetAddress());
          if(p.x>=1) MinerecursionLeft(cl,(le*y+x-1+cl)->GetAddress());
          if((p.x>=1)&&(p.y+1<le)) MinerecursionLeftDown(cl,(le*(y+1)+x-1+cl)->GetAddress());
          if(p.y>=1)  MinerecursionUp(cl,(le*(y-1)+x+cl)->GetAddress());
    }
}


/**********************************************************************************************/

void  ClickLabel::MinerecursionRightDown(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
        if(p.y+1<le)   MinerecursionDown(cl,(le*(y+1)+x+cl)->GetAddress());
        if((p.x+1<le)&&(p.y>=1)) MinerecursionRightUp(cl,(le*(y-1)+x+1+cl)->GetAddress());
        if(p.x+1<le) MinerecursionRight(cl,(le*y+x+1+cl)->GetAddress());
        if((p.x+1<le)&&(p.y+1<le)) MinerecursionRightDown(cl,(le*(y+1)+x+1+cl)->GetAddress());
    }
}

/**********************************************************************************************/
void  ClickLabel::MinerecursionUp(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
//          if((p.x>=1)&&(p.y>=1)) MinerecursionUp(cl,(le*(y-1)+x-1+cl)->GetAddress());
//          if(p.x>=1) MinerecursionUp(cl,(le*y+x-1+cl)->GetAddress());
//          if((p.x>=1)&&(p.y+1<le)) MinerecursionUp(cl,(le*(y+1)+x-1+cl)->GetAddress());
        //yes
          if(p.y>=1)  MinerecursionUp(cl,(le*(y-1)+x+cl)->GetAddress());
    }
}

/**********************************************************************************************/
void  ClickLabel::MinerecursionDown(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
        //yes
        if(p.y+1<le)   MinerecursionDown(cl,(le*(y+1)+x+cl)->GetAddress());
//        if((p.x+1<le)&&(p.y>=1)) MinerecursionDown(cl,(le*(y-1)+x+1+cl)->GetAddress());
//        if(p.x+1<le) MinerecursionDown(cl,(le*y+x+1+cl)->GetAddress());
//        if((p.x+1<le)&&(p.y+1<le)) MinerecursionDown(cl,(le*(y+1)+x+1+cl)->GetAddress());
    }
}
/**********************************************************************************************/
void  ClickLabel::MinerecursionLeft(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));

        //yes
          if(p.x>=1) MinerecursionLeft(cl,(le*y+x-1+cl)->GetAddress());
//          if((p.x>=1)&&(p.y>=1)) MinerecursionLeftUp(cl,(le*(y-1)+x-1+cl)->GetAddress());
//          if((p.x>=1)&&(p.y+1<le)) MinerecursionLeftUp(cl,(le*(y+1)+x-1+cl)->GetAddress());
//          if(p.y>=1)  MinerecursionUp(cl,(le*(y-1)+x+cl)->GetAddress());
    }
}

/**********************************************************************************************/
void  ClickLabel::MinerecursionRight(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
        //yes
        if(p.x+1<le) MinerecursionRightDown(cl,(le*y+x+1+cl)->GetAddress());
//        if(p.y+1<le)   MinerecursionDown(cl,(le*(y+1)+x+cl)->GetAddress());
//        if((p.x+1<le)&&(p.y>=1)) MinerecursionRightDown(cl,(le*(y-1)+x+1+cl)->GetAddress());
//        if((p.x+1<le)&&(p.y+1<le)) MinerecursionRightDown(cl,(le*(y+1)+x+1+cl)->GetAddress());
    }
}
/**********************************************************************************************/
void  ClickLabel::MinerecursionLeftDown(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
//          if((p.x>=1)&&(p.y>=1)) MinerecursionLeftUp(cl,(le*(y-1)+x-1+cl)->GetAddress());
//          if(p.x>=1) MinerecursionLeft(cl,(le*y+x-1+cl)->GetAddress());
          if((p.x>=1)&&(p.y+1<le)) MinerecursionLeftDown(cl,(le*(y+1)+x-1+cl)->GetAddress());
//          if(p.y>=1)  MinerecursionUp(cl,(le*(y-1)+x+cl)->GetAddress());
    }
}
/**********************************************************************************************/
void  ClickLabel::MinerecursionRightUp(ClickLabel * cl,Point p)
{
    Level le = systemLevel;
    int x = p.x, y = p.y; //当前指针坐标
    int count = (le*y+x+cl)->GetArroundMine(); //当前块周围雷数
    if(count!=0) //周围雷数不为0 显示个数
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Panel | QFrame::Plain );
        QString Minecount = QString::number(count);
        (le*y+x+cl)->setText(Minecount);
    }
    else //为0，递归旁边8个块
    {
         (le*y+x+cl)->setFrameStyle( QFrame::Box | QFrame::Raised );  //翻开 显示0
         (le*y+x+cl)->setText(tr("0"));
        //yes
        if((p.x+1<le)&&(p.y>=1)) MinerecursionRightUp(cl,(le*(y-1)+x+1+cl)->GetAddress());

//        if(p.y+1<le)   MinerecursionDown(cl,(le*(y+1)+x+cl)->GetAddress());
//        if(p.x+1<le) MinerecursionRightDown(cl,(le*y+x+1+cl)->GetAddress());
//        if((p.x+1<le)&&(p.y+1<le)) MinerecursionRightDown(cl,(le*(y+1)+x+1+cl)->GetAddress());
    }
}
/**********************************************************************************************/
