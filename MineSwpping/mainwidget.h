#ifndef MAINWIGDET_H
#define MAINWIGDET_H
#include <QDebug>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include "clicklabel.h"
#include "publicdate.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public :
    MainWidget(QWidget *parent, Level le);
    ~MainWidget();
    void MainWidgetDesk(Level le);

private slots:
    void TimeUpdate(void);
    void TimeStop(void);
public:
    QTimer *timer;
private:
    ClickLabel * clickLabel ;
    QLabel *timeLabel, *counter;
    QPushButton * emoticon;
    QLineEdit *lineEdit;

    QLabel * testLabel;
    QLineEdit *testEdit;
    QVBoxLayout *mainLayout;
};
#endif // MAINWIGDET_H
