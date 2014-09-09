
///////////  COSTANTI  GESTIONE  SCHEMI ////////////////////////////

const byte LEFT_SPACE=5;
const byte OVER_SPACE=5;
const byte RIGHT_SPACE=5;
const byte BOTTOM_SPACE=5;

const int RESOLUTION_X=320;
const int RESOLUTION_Y=240;

const int UNITX=8;								//	8
const int UNITY=(int)(UNITX/1.0);	  			//	8

const int NSPRITEX=(int)(RESOLUTION_X/UNITX);	//	40
const int NSPRITEY=(int)(RESOLUTION_Y/UNITY);	//	30
const int SPRITETOT=NSPRITEX*NSPRITEY;	//Numero totale degli sprite
										// effettivamente visibili.

const int MASKX=(int)NSPRITEX+LEFT_SPACE+RIGHT_SPACE; 	//	50
const int MASKY=(int)NSPRITEY+OVER_SPACE+BOTTOM_SPACE; 	//	40
const int MASKTOT=MASKX*MASKY;			//Numero complessivo dei blocchi
										// della mappa.

//const byte NXTEXTFILE=16;
//const byte NYTEXTFILE=16;

		// Numero di pixel non visibili
const byte Y_OFFSET=UNITY*OVER_SPACE;	//
const byte X_OFFSET=UNITX*LEFT_SPACE;
const byte Y2_OFFSET=UNITY*BOTTOM_SPACE;
const byte X2_OFFSET=UNITY*RIGHT_SPACE;

//////////////////// COSTANTI  GENERICHE  ////////////////

const byte DIR_LEFT=4;
const byte DIR_LEFTUP=7;
const byte DIR_UP=8;
const byte DIR_RIGTUP=9;
const byte DIR_RIGHT=6;
const byte DIR_RIGDOW=3;
const byte DIR_DOWN=2;
const byte DIR_LEFDOW=1;
const byte DIR_CENTRE=5;

///////////////  SPRITE  E  TERRENO  /////////////////////////////////
		// Se esistono i parametri SOLID SOLID_LIMIT non ha motivo
		// di esistere.
//const SOLID_LIMIT=5;	// Limite : agli sprite con valore inferiore
						// 			si pu• passare attraverso, a quelli
						//			con valore superiore o uguale no.

const byte AIR=0;
const byte STAIRS=3;			//	Scale
const byte CLIMB_TERR=5;		//
const byte WALL=9;

//const byte UPLEFT=7;			// 	Scala \\ ;
//const byte UPRIGHT=9;			//	Scala // ;

	// Campo di bit che dovrebbe contenere solidit… e tipo di terreno.

/*struct level{
		byte solid	:	4;
		byte terran	:	4;
		byte sprite	:	8;
		};*/

	//	Maschera e costanti per le solidit… di uno schema

const byte ALLSOLID=3;

const byte SEMISOLID=1;
const byte NOSOLID=0;


	//	Maschera per i tipi di terreno dello schema

//level mask[MASKY][MASKX];
