#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent, Level le)
    :QWidget(parent)
{
    MainWidgetDesk(le);
}

MainWidget::~MainWidget()
{
    qDebug()<<"quit subwidget class";
    delete[] clickLabel;
}

void MainWidget::MainWidgetDesk(Level le)
{
    QIcon button_ico(":/z_run.jpg");
    emoticon = new QPushButton;
    emoticon->setMinimumSize(33,33);
    emoticon->setMaximumSize(50,50);
    emoticon->setIcon(button_ico);
    emoticon->setIconSize(QSize(50,50));
    connect(emoticon, SIGNAL(clicked()), this, SLOT(TimeStop()));

    counter = new QLabel;
    counter->setText(tr("剩余个数:  "));

    timeLabel = new QLabel;
    timer = new QTimer(this);
    timer->setInterval(1000); // 每次发射timeout信号时间间隔为1秒
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeUpdate()));
    timeLabel->setText(tr("进行时间: 0:0"));
//    timer->start();

    QLabel * spalte = new QLabel;
    spalte->setFixedSize(le*45,40);
    spalte->setFrameStyle( QFrame::Box | QFrame::Raised );
    spalte->setLineWidth( 4 );
    spalte->setMidLineWidth(1);
    spalte->setText(tr("Mine area"));

    clickLabel = new ClickLabel[le*le];
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(counter);
    topLayout->addWidget(emoticon);
    topLayout->addWidget(timeLabel);
    topLayout->setSpacing(le*10);

    QHBoxLayout *secondLayout = new QHBoxLayout;
    secondLayout->addWidget(spalte);
    QGridLayout * thirdLayout = new QGridLayout;
    for(int j=0;j<le;j++)
        for(int i=0;i<le;i++)
            thirdLayout->addWidget(le*j+clickLabel+i,0+j,0+i,1,1);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout,0);
    mainLayout->addLayout(secondLayout,1);
    mainLayout->addLayout(thirdLayout,2);
    this->setLayout(mainLayout);
}

void MainWidget::TimeUpdate(void)
{
        static int second = 0,minute = 0;
        second++;
        if(second ==60)
        {
            minute++;
            second = 0;
        }
        QString scondstr = QString::number(second);
        QString minutestr = QString::number(minute);
        timeLabel->setText("进行时间: "+minutestr+":"+scondstr);
}

void MainWidget::TimeStop(void)
{
    static int count = 0;
    count++;

    if(count%2 == 1)
    {
             timer->stop();
             emoticon->setIcon(QIcon(":/z_pause.jpg"));
    }

    else
    {
            timer->start();
            emoticon->setIcon(QIcon(":/z_run.jpg"));
    }
}


