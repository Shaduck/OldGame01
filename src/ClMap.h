
#ifndef CLMAP_H
#define CLMAP_H

#include <allegro.h>
#include "default.h"

#include "ClLevel.h"
#include "ClTexture.h"


///////////////////////////////////////////////////////////////////////
//GRANDE CLASSE CHE GESTISCE LIVELLI E TEXTURE (TILE IN INCOGNITO) ;)//
///////////////////////////////////////////////////////////////////////

	//  Costanti.hpp e Common.hpp sono esterni.


class T_Map{

			T_Level *Mappa;
			int NLevel;
			//int CurrentLev;		// Livello corrente


			T_Texture *Texture;
			int NTexture;
			//int CurrentText;	// Set di Texture corrente


		// Per un po' di tempo credo che le palette saranno gestite
		// da una classe esterna
			//PALETTE *Palette;
			//int NPalette;
			//int CurrentPal;		//	Palette corrente


		///////////////// QUESTI VALORI SONO NEL FILE DELLE
		/////////////////  COSTANTI
			//byte Ncolor;   		// Numero di colori per lo sfondo
			//byte StartColor;	// Numero dove inizia il set di
								// colori dello sfondo

			// Quando si carica la Palette non si scrivono tutti i
			// colori, ma solo quelli che verranno usati dallo sfondo:
			// Ad es. Sfondo= colori da 30 a 60


			// Puntatori alle zone di memoria esterne che verranno
			// lette dalle funzioni esterne: gestione dei personaggi
			// e puttaggio immagini

			//byte *MaskText;		// temporanea per il passaggio dei
								// dati da T_Level a T_Texture

		public:

			T_Map(void);
			~T_Map(void);

				//  Funzioni del gioco  //

			byte SetTextureFile(char *filedat,int ntext);
 							// Carica le texture

			bool SetMapFile(char *nome,int nlev);		// Carica i livelli
										// Nome del file che contiene
							// le mappe dei livelli.
							// La prima cosa da leggere Š un int con il
							// numero di mappe nel file


			//byte OutLevel(int level,int text);
			// Carica il livello corrente con le texture indicate
			// Parametri:
			// 	level: il codice del livello
			//	leftlev: codice del lovello sinistro
			// 	toplev: codice del livello superiore
			// 	rightlev: codice del livello destro
			// 	bottomlev: codice del livello inferiore
			// 	texture: codice delle texture da usare
			byte OutLevel(int level,int leftlev,int toplev,
							int rightlev,int bottomlev,int texture);

			/////////////  FUNZIONI PER LA MANUTENZIONE  ///////////////

			bool LoadMap(FILE *fp);
			bool SaveMap(FILE *fp);

			int RetNLevel(void);
			void SetNLevel(int nlev);

			bool InsertNLevel(int numlev,T_Level &newlvl);

			int RetNText(void);
			void RetTextBmp(int ntext,BITMAP *temp);

		};

#endif
