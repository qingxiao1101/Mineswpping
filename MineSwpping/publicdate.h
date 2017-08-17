#ifndef PUBLICDATE_H
#define PUBLICDATE_H
#include "QEvent"
class MainWindow;
class ClickLabel;
enum Level
{
    Level1=6,Level2=8,Level3=10
};

enum GameType
{
    gameOver = 1100,
    gameWinn
};

extern Level systemLevel;
extern ClickLabel * minePointer;
extern MainWindow * mainwindow;
extern int sumMineCount;
extern int sumFlag;
QEvent::Type GetGameEventType(GameType);

#endif // PUBLICDATE_H
