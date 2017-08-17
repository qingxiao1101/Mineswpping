#ifndef CLICKLABEL_H
#define CLICKLABEL_H
#include <QLabel>
#include "corealgorithem.h"
#include "publicdate.h"
#include "mainwidget.h"
#include <QCoreApplication>
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
       void SetVisited(bool);
       bool GetVisited(void)const;
       void BfsResearch(ClickLabel *cl,Point p);
       Point Adjction(Point p); //

   signals:
       // 鼠标单击信号
       void leftclicked();//IMClickLabel* label);
       void rightclicked();
       //game over
       void gameover();

   protected:
       // 鼠标单击事件
       void mouseReleaseEvent(QMouseEvent *);
       void mousePressEvent(QMouseEvent *event);
       void enterEvent(QEvent *);
       void leaveEvent(QEvent *);
   public slots:
       void LeftMausClick(void);
       void RightMausClick(void);
       void Testsignal(void);

private:
       Point position;
//       int x,y;
       int arroundMine;
       bool flag;
       int attribute;
       bool openFlag;
       bool visited;

};

#endif // CLICKLABEL_H
