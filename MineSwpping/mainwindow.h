#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "publicdate.h"
#include "mainwidget.h"
#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, Level);
    ~MainWindow();
    void MainWindowInit(void);
    void MainWindowDesk(void);
    void SetAction(void);
    void SetMenuOption(void);

protected slots:
    void OpenGame(void);
    void CloseGame(void);
    void SetGame1(void);
    void SetGame2(void);
    void SetGame3(void);

private:
    Ui::MainWindow *ui;
    QMenu * menu;
//    QHBoxLayout *mainLayout;
    MainWidget * mainwidget;
    QAction *openAction;
    QAction *closeAction;
    QAction *levelAction[3];
};

#endif // MAINWINDOW_H
