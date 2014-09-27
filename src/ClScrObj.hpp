#ifndef CLSCREENOBJ_HPP
#define CLSCREENOBJ_HPP

#include <allegro.h>
#include "default.h"

	//  Alcune costanti devono essere esterne:
	//	-	UNTIX	= 	Larghezza dei blocchi unitari
	//	-	UNITY	=	Altezza dei blocchi unitari

class T_ScreenObj{

		public:
			BITMAP *image;			// *image[n]  tante immagini!! :))
					// NO! 1 solo, il puntatore viene aggiornato dalle
					// classi derivate!! ^__^ ( che brutta faccia !! )

		private:
			int coordx,coordy;      // Coordinate del punto inferiore
									// sinistro dell'oggetto sullo schermo

			byte nunitx,nunity;		// Numero blocchi che compongono
									// l'oggetto.

			int	chlargh;			// Larghezza complessiva
									// dell'oggetto
			int chaltezz;			// Altezza complessiva
									// dell'oggetto

			byte normaly,crouchy;	// Numero blocchi del personaggio
									// in piedi o accucciato

			int nleftcp;			// Numero dei punti di controllo
			int ntopcp;				//  delle collisioni   left, top

			byte *leftcp;			// Array dei punti di controllo
			byte *topcp;			//   	left,top

			bool move;				// E' un oggetto che si muove o no?

		public:

			T_ScreenObj(void);
			~T_ScreenObj(void);

/////////////////////////  GESTIONE  ///////////////////////////////////

			void InitScreenObj(byte x,byte y);

			void InitImage(BITMAP *newimage);

////////////////////////////////////////////////////////////////////////


////////////////////// SETTAGGI  DEL  PERSONAGGIO  /////////////////////


////////////////////////////////////////////////////////////////////////


/////////////////////  CONTROLLO  MOVIMENTI  ///////////////////////////

			void setposition(int x,int y);
			void setcoordx(int x);
			void setcoordy(int y);


			// 	controlla se almeno uno dei punti di controllo
			// 	corrisponde al terreno selezionato

			bool testall(byte terr);

			//	terr: tipo di terreno che deve essere sia all'estremo
 			//	dx che all'estremo sx (compresi) se il tipo di terreno
 			//	Š pi— stretto del personaggio, non si pu• centrare

			//	controlla se il personaggio pu• essere centrato
			// 	su un tipo di terreno : 0 se non pu•,
			//  DIR_LEFT se deve andare a sx,
			//  DIR_RIGHT se deve andare a dx,
			//	DIR_CENTRE se Š centrato;

			byte testint(byte y,byte terr);		// linea y di test
			byte testbottom(byte terr);			// livello dei piedi
			byte testunder(byte terr,byte pos = 0);	// sotto i piedi
			byte testtop(byte terr);			// livello della testa
			byte testover(byte terr,byte pos = 0);	// sopra la testa

			byte TestBorder(void);				// controlla se il 'coso'
												// ha un lato esterno alla
												// schermata

			//	ritorna 0 se non Š centrato, 1 se Š centrato
			//bool centreint(byte y,byte terr);	// linea y di test
			//bool centrebottom(byte terr);
			//bool centretop(byte terr);

////////////////////////////////////////////////////////////////////////


////////////////// MOVIMENTO DEL PERSONAGGIO (PLATFORM) ////////////////

		//		Movimenti del personaggio

			void gocrouch(void);
			void goraise(void);

			bool godown(byte sollim,byte dis);
			bool goleft(byte sollim,byte dis);
			bool goright(byte sollim,byte dis);
			bool goup(byte sollim,byte dis);

////////////////////////////////////////////////////////////////////////

/////////////////  GESTIONE  IMMAGINE  /////////////////////////////////

			void outimage(BITMAP *out);

////////////////////////////////////////////////////////////////////////


		};

#include"ClScrObj.cpp"

#endif