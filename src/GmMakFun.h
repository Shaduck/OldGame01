
#ifndef _GMMAKFUN_H_
#define _GMMAKFUN_H_


void GameInit(void);
void GameExit(void);

void DrawMainWindow(void);
void DrawMiniWindow(void);
void DrawTileLists(void);

void MoveTileBar(int direction,int barnum);

void DrawTerranBar(void);
void DrawSolidBar(void);

void PrintBlock(void);

int MouseDetectClick(void);

void InitMPoints(void);

#endif
