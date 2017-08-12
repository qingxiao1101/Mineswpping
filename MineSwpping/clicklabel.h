#ifndef CLICKLABEL_H
#define CLICKLABEL_H
#include <QLabel>
#include "clicklabel.h"

class ClickLabel : public QLabel
{
    Q_OBJECT
   public:
       explicit ClickLabel(QWidget *parent = 0);
       ClickLabel(const QString &text, QWidget *parent=0);
   signals:
       // 鼠标单击信号
       void clicked();//IMClickLabel* label);

   protected:
       // 鼠标单击事件
       void mouseReleaseEvent(QMouseEvent *);
       void enterEvent(QEvent *);
       void leaveEvent(QEvent *);
   public slots:
       void MausClick(void);
};

#endif // CLICKLABEL_H
