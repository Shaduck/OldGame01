
#ifndef _COMMON_H_
#define _COMMON_H_

#include <cstdio>

#include <allegro.h>

#include "default.h"
#include "costanti.h"

extern FILE *filelog;


extern BITMAP *buffer;
extern BITMAP *sfondo;
//BITMAP *textures;
//BITMAP *textarch[2];
extern RGB color[256];
extern bool changed;
//RGB colorarch[2][256];

extern byte MaskText[SPRITETOT];

extern byte terreno[RESOLUTION_Y+Y_OFFSET+Y2_OFFSET]
	 				[RESOLUTION_X+X_OFFSET+X2_OFFSET];
	 
extern byte solid[RESOLUTION_Y+Y_OFFSET+Y2_OFFSET]
					[RESOLUTION_X+X_OFFSET+X2_OFFSET];

#endif
