typedef unsigned char byte;

#include"Costanti.cpp"
#include"Common.hpp"
#include"ClMap.hpp"

const int BIGUNITX=16;				// Dimensione del cursore a dimensione
const int BIGUNITY=16;				// raddoppiata

const byte MAX_TERR=9;
const byte MAX_SOLID=2;

///////////////// COSTANTI  DEGLI  OGGETTI  A  VIDEO /////////////////////

/////////////////// CONTATORE DEI LIVELLI DELLA MAPPA //////////////

const int MAPCOUNTBARX=0;
const int MAPCOUNTBARY=0;
const int MAPCOUNTLARGH=100;
const int MAPCOUNTALT=10;

//////////////////////////////////////////////////////////////////

////////////////////// FINESTRA PRINCIPALE ///////////////////////

// Dimensione delle texture nell'editor
const int MUNITX=5;								//  20	12	10
const int MUNITY=MUNITX;	  			//	16	10	 8

const int XLAR=MUNITX*NSPRITEX;		// Larghezza della schermata dell'editor
const int YLAR=MUNITY*NSPRITEY;		// della mappa

const int MAINWINDX=0;
const int MAINWINDY=10;
const int MAINWINDLARGH=XLAR;		//200;
const int MAINWINDALT=YLAR;		//150;

///////////////////////////////////////////////////////////////////

////////////////////////// FINESTRA LATERALE //////////////////////

const byte WIMGOFFX=2;				// Numero di unit… a dx e a sx di quella
									// centrale nella finestra a grandezza
									// naturale.
const byte WIMGOFFY=2;				// Numero di unit… in alto e in basso
const byte WIMGX=(WIMGOFFX*2)+1;	// Larghezza e altezza complessiva in
const byte WIMGY=(WIMGOFFY*2)+1;	// numero di unit…
const byte NWINDIMG=WIMGX*WIMGY;	// Numero di blocchi
//byte miniwmask[WIMGY][WIMGX];			// matrice della finestra


const int MINIWINDX=280;
const int MINIWINDY=10;
const int MINIWINDLARGH=WIMGX*UNITX;	//40;
const int MINIWINDALT=WIMGY*UNITY;	//40;

///////////////////////////////////////////////////////////////////

////////////////////// BARRE DELLE TEXTURE ////////////////////////

byte selectbar=0;
const int NBARTEXT=16;

const int TEXTBAR1X=0;
const int TEXTBAR1Y=220;

const int TEXTBAR2X=160;
const int TEXTBAR2Y=220;

const int TEXTBARLARGH=(NBARTEXT+2)*UNITX;
const int TEXTBARALT=UNITY*2;

///////////////////////////////////////////////////////////////////

/////////////////// BARRE DELLA SOLIDITA' /////////////////////////
				//	( Š un'arma di Diablo II ?? (!) )

//byte selectbar=0;
const int NBARSOLID=4;

const int SOLIDBAR1X=0;
const int SOLIDBAR1Y=215;

const int SOLIDBAR2X=160;
const int SOLIDBAR2Y=215;

const int SOLIDBARLARGH=(NBARSOLID+2)*UNITX;
const int SOLIDBARALT=UNITY*2;

///////////////////////////////////////////////////////////////////

///////////////////// BARRE DEL TERRENO ///////////////////////////

//byte selectbar=0;
const int NBARTERR=4;

const int TERRBAR1X=0;
const int TERRBAR1Y=205;

const int TERRBAR2X=160;
const int TERRBAR2Y=205;

const int TERRBARLARGH=(NBARTERR+2)*UNITX;
const int TERRBARALT=UNITY*2;

///////////////////////////////////////////////////////////////////

/////////////// VARIABILI DI CONTROLLO ////////////////////////////

//int i,j,k,x,y;

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
const int NMOUSEPOINT=8;
					// Numero di punti 'sensibili' dello schermo

int MouseP[NMOUSEPOINT][4];

	