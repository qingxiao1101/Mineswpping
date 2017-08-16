#ifndef CLICKLABEL_H
#define CLICKLABEL_H
#include <QLabel>
#include "corealgorithem.h"
#include "publicdate.h"
#include "mainwidget.h"
struct Point{
    int x,y;
    bool operator == (const Point& tmp);
    Point(int xx,int yy);
    Point();
};

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
       explicit ClickLabel(QWidget *parent = 0);
       ClickLabel(const QString &text, QWidget *parent=0);
       void SetAttribute(int);
       int GetAttribute(void) const;
       void SetAddress(int x, int y);
       Point GetAddress(void) const;
       void SetArroundMine(int);
       int GetArroundMine(void) const;
       void SetFlag(bool);
       bool GetFlag(void)const;
       void SetOpenFlag(bool);
       bool GetOpenFlag(void)const;
       void Minerecursion(ClickLabel * cl,Point p);
       void MinerecursionLeftUp(ClickLabel * cl,Point p);
       void MinerecursionRightDown(ClickLabel * cl,Point p);
       void MinerecursionUp(ClickLabel * cl,Point p);
       void MinerecursionDown(ClickLabel * cl,Point p);
       void MinerecursionLeft(ClickLabel * cl,Point p);
       void MinerecursionRight(ClickLabel * cl,Point p);
       void MinerecursionLeftDown(ClickLabel * cl,Point p);
       void MinerecursionRightUp(ClickLabel * cl,Point p);
   signals:
       // 鼠标单击信号
       void leftclicked();//IMClickLabel* label);
       void rightclicked();

   protected:
       // 鼠标单击事件
       void mouseReleaseEvent(QMouseEvent *);
       void mousePressEvent(QMouseEvent *event);
       void enterEvent(QEvent *);
       void leaveEvent(QEvent *);
   public slots:
       void LeftMausClick(void);
       void RightMausClick(void);

private:
       Point position;
//       int x,y;
       int arroundMine;
       bool flag;
       int attribute;
       bool openFlag;

};

#endif // CLICKLABEL_H
