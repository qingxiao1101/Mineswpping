#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MainWindowDesk(void);
    void SetAction(void);
    void SetMenuOption(void);

protected slots:
    void OpenGame(void);
    void CloseGame(void);

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
