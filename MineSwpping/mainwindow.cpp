#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//set main windows
    this->resize(300, 200);
    this->setWindowTitle(tr("扫雷"));
    //set main menu
        MainWindowDesk();
    //set main widget
    mainwidget = new MainWidget();
    this->setCentralWidget(mainwidget);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindowDesk(void)
{
//动作定义
    SetAction();
//选项菜单 界面布局
    SetMenuOption();

}
void MainWindow::SetAction(void)
{
    openAction = new QAction(tr("&开始"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a file."));
    connect(openAction, SIGNAL(triggered()), this, SLOT(OpenGame()));

    closeAction = new QAction(tr("&关闭"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close a file."));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(CloseGame()));

    levelAction[0] = new QAction(tr("&Level1"), this);
    levelAction[1] = new QAction(tr("&Level2"), this);
    levelAction[2] = new QAction(tr("&Level3"), this);
}

void MainWindow::SetMenuOption(void)
{
    menu = menuBar()->addMenu(tr("&选项"));
    menu->addAction(openAction);
    QMenu * submenu = menu->addMenu(tr("&难度选择"));
    menu->addAction(closeAction);

    submenu->addAction(levelAction[0]);
    submenu->addAction(levelAction[1]);
    submenu->addAction(levelAction[2]);
//帮助菜单
    QMenu * help = menuBar()->addMenu(tr("&帮助"));
    help->addMenu(" about ");
}

void MainWindow::OpenGame(void)
{
   QMessageBox::warning(this, tr("提示"), tr("Game Beginn"),
                                   QMessageBox::Yes | QMessageBox::No);
}

void MainWindow::CloseGame(void)
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QString str;
   switch(QMessageBox::information(this, tr("提示"), tr("Do you want to quit the Game?"),
                                   QMessageBox::Yes | QMessageBox::No))
   {
         case QMessageBox::Yes: this->close(); break;
         case QMessageBox::No:
         default: break;
   }
}





