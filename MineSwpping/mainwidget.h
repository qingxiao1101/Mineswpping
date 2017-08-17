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
#include "corealgorithem.h"

class   ClickLabel;
//enum Level;
class MainWidget : public QWidget
{
    Q_OBJECT

public :
    MainWidget(QWidget *parent, Level le);
    ~MainWidget();
    void MainWidgetDesk(Level le);
    void SetStatusBar(void);
    void  SetClickLabel(Level);
    void SetMainWidgetLayout(Level le);

private slots:
    void TimeUpdate(void);
    void TimeStop(void);
public:
    QTimer *timer;
     ClickLabel * clickLabel ;
private:
    QLabel *timeLabel, *counter;
    QPushButton * emoticon;
    QLineEdit *lineEdit;

    QLabel * testLabel;
    QLineEdit *testEdit;
    QVBoxLayout *mainLayout;
};
#endif // MAINWIGDET_H
