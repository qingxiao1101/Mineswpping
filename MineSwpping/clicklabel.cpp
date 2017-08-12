#include <QMouseEvent>
#include "clicklabel.h"

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
    setText(tr("0"));
    connect(this, SIGNAL(clicked()), this, SLOT(MausClick()));
}

ClickLabel::ClickLabel(const QString &text, QWidget *parent) :
    QLabel(parent)
{
    setText(text);
}

// mark: protected:------------------------------------------------
void ClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked();//(this);
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


void ClickLabel::MausClick(void)
{
    setFrameStyle( QFrame::Panel | QFrame::Plain );
    this->setText(tr("ok"));
}

