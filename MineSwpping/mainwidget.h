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
#include <QIcon>

class MainWidget : public QWidget
{
    Q_OBJECT

public :
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void MainWidgetDesk(void);

private slots:
    void TimeUpdate(void);
    void TimeStop(void);

private:
    QLabel *timeLabel, *counter;
    QPushButton * emoticon;
    QLineEdit *lineEdit;
    QTimer *timer;
    QLabel * testLabel;
    QLineEdit *testEdit;
    QVBoxLayout *mainLayout;
};
#endif // MAINWIGDET_H
