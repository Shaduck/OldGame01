
#include "GmMakDef.h"


////////////////////// BARRE DELLE TEXTURE ////////////////////////

byte selectbar=0;

/////////////// DEGLI OGGETTI A VIDEO  ////////////////////////////

T_Map mappa;
int currentlevel=0;

T_Level livello;

BITMAP *textures;			//	Immagine globale delle texture
BITMAP *sprites[256];		// 	Array degli sprite

BITMAP *sldbmp;				// Immagine globale delle solidit… :)
BITMAP *solidimg[4];

BITMAP *terbmp;
BITMAP *terrainimg[10];
//RGB color[256];

byte mainwind[NSPRITEY][NSPRITEX];
int cursorx=0,cursory=0;

byte miniwmask[WIMGY][WIMGX];

byte spritemask[2][2][NBARTEXT];
int currenttile[2];
byte cursize=1;

byte terranmask[4]={0,3,5,9};
byte currentterran[2]={0,0};

byte solidmask[3]={0,1,3};
byte currentsolid[2]={0,0};

//byte spritemask2[2][18];
//int currenttile2;

/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


byte CURS_COL=7;
byte CONF_COL=3;
byte BACKG_COL=5;
byte DESK_COL=0;

///////////////////////////////////////////////////////////////////

/////////////////////////// GESTIONE MOUSE ////////////////////////

int MWind;			// Usata nel prog per identificare il punto
					// sensibile(!!) in cui si Š clickato

int MouseP[NMOUSEPOINT][4];

	