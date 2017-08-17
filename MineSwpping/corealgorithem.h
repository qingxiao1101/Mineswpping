#ifndef COREALGORITHEM_H
#define COREALGORITHEM_H
#include "publicdate.h"
#include "clicklabel.h"

class ClickLabel;
struct Point;
Point *  SetMineRand(Level);
void MineLayout(ClickLabel * cl,Level le);
int MineCounterOneCircuit(ClickLabel * cl, Point p,Level le);
//void Minerecursion(ClickLabel * cl,Point p);

#endif // COREALGORITHEM_H
