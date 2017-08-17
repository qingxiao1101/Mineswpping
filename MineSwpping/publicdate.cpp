#include "publicdate.h"
#include "clicklabel.h"
#include "mainwindow.h"

Level systemLevel = Level1;
MainWindow * mainwindow=NULL;
ClickLabel * minePointer = NULL;
int sumMineCount = 0;
int sumFlag = 0;
//声明、定义、注册自定义事件类型，事件ID为自定义事件ID起点QEvent::User +100=1100
 static const QEvent::Type GameOverType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);
 static const QEvent::Type GameWinnType = (QEvent::Type)QEvent::registerEventType(QEvent::User+101);
QEvent::Type GetGameEventType(GameType gt)
{
    if(gt==gameOver)
    return GameOverType;
    else if(gt==gameWinn)
     return GameWinnType;
}
