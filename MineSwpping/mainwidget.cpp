#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    :QWidget(parent)
{
    MainWidgetDesk();
}

MainWidget::~MainWidget()
{
    qDebug()<<"quit subwidget class";
}

void MainWidget::MainWidgetDesk(void)
{
    QIcon button_ico(":/z_run.jpg");
    emoticon = new QPushButton;
    emoticon->setMinimumSize(33,33);
    emoticon->setMaximumSize(50,50);
    emoticon->setIcon(button_ico);
    emoticon->setIconSize(QSize(50,50));
    connect(emoticon, SIGNAL(clicked()), this, SLOT(TimeStop()));

    counter = new QLabel;
    counter->setText(tr("Rest:  "));

    timeLabel = new QLabel;
    timer = new QTimer(this);
    timer->setInterval(1000); // 每次发射timeout信号时间间隔为1秒
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeUpdate()));
    timeLabel->setText(tr("      0:0"));
    timer->start();

    testLabel = new QLabel;
    testLabel->setText(tr("test label"));
    testEdit = new QLineEdit;
    testEdit->setText(tr("test line"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(counter);
    topLayout->addWidget(emoticon);
    topLayout->addWidget(timeLabel);
    QHBoxLayout * secondLayout = new QHBoxLayout;
    secondLayout->addWidget(testLabel);
    secondLayout->addWidget(testEdit);
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout,0);
    mainLayout->addLayout(secondLayout,1);
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
        timeLabel->setText("      "+minutestr+":"+scondstr);
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


