#ifndef CLCHAR_HPP
#define CLCHAR_HPP

#include<allegro.h>
#include<default.h>

#include"D:\djgpp\game01\ClScrObj.hpp"

	//  Alcune costanti devono essere esterne:
	//	-	UNTIX	= 	Larghezza dei blocchi unitari
	//	-	UNITY	=	Altezza dei blocchi unitari

const byte PLAYER_LARGH=2;
const byte PLAYER_ALT=4;

const byte MOVE_DELAY=1;

const byte JUMP_DELAY=2;

const byte CLIMB_DELAY=1;

const byte STAIRS_DELAY=12;
const byte NSTFRAME=2;	//UNITY/2;

const byte SPEFALL=5;		//Velocit… massima di caduta
const byte SPEXNORM=1;		// Velocit… di crociera
const byte SPEXRUN=2;		// Velocit… della corsa
const byte SPEJUMP=5;		// Velocit… iniziale del salto
const byte SPEYUP=1;
const byte SPEYDOWN=1;


class T_Character : public T_ScreenObj{

			//byte var1;				// Variabili varie che sono sempre
									//	utili :)

			//int life;


// 	Da notare che i player.'stats' indicano se state eseguendo una
//	determinata azione :
//	-	player.move 	= il personaggio si sta muovendo
//	-	player.climb	=  si sta arrampicando
//					(attenzione: Š settato solo quando il personaggio
//						deve arrampicarsi, non quando Š attaccato
//						ad una scala. )
//	-	ecc.

			struct st1{
				bool move	:1;
				bool run	:1;
				bool crouch	:1;
				bool graspcl:1;
				bool graspst:1;
				bool climb	:1;
				bool stairs	:1;
				bool jump	:1;
				bool hitted	:1;
				bool attack	:1;
				bool fall	:1;
			}status;

			byte jumpdelay;

		//public:
		//	BITMAP *image;			// *image[n]  tante immagini!! :))

		private:
			//int coordx,coordy;      // Coordinate del punto inferiore
									// sinistro del personaggio
			byte dirx,diry;			// Direzione del player :
									// Orizzontali e verticali

			byte movecont;

			byte climbcont;

			byte stairstest;
			byte stairscont;
			byte stairsflag;
			byte stairsstx[NSTFRAME];
			byte stairssty[NSTFRAME];

			byte speedx;			// Velocit… orizzontale
			byte speedjump;			// Velocit… del salto
			byte speedfall;			// Velocit… di caduta


			//byte nunitx,nunity;		// Numero blocchi che compongono
									// il personaggio.


		//	int	chlargh;			// Larghezza complessiva
									// del player
		//	int chaltezz;			// Altezza complessiva
									// del player

		//	int nleftcp;			// Numero dei punti di controllo
		//	int ntopcp;				//  delle collisioni   left, top

		//	byte *leftcp;			// Array dei punti di controllo
		//	byte *topcp;			//   	left,top


		public:

			T_Character(void);
			~T_Character(void);

/////////////////////////  GESTIONE  ///////////////////////////////////

			void InitCharacter(byte x,byte y);

////////////////////////////////////////////////////////////////////////


////////////////////// SETTAGGI  DEL  PERSONAGGIO  /////////////////////


////////////////////////////////////////////////////////////////////////


/////////////////////  CONTROLLO  MOVIMENTI  ///////////////////////////

	//		void setposition(int x,int y);
	//		void setcoordx(int x);
	//		void setcoordy(int y);


			// 	controlla se almeno uno dei punti di controllo
			// 	corrisponde al terreno selezionato

	//		bool testall(byte terr);

			//	terr: tipo di terreno che deve essere sia all'estremo
 			//	dx che all'estremo sx (compresi) se il tipo di terreno
 			//	Š pi— stretto del personaggio, non si pu• centrare

			//	controlla se il personaggio pu• essere centrato
			// 	su un tipo di terreno : 0 se non pu•,
			//  DIR_LEFT se deve andare a sx,
			//  DIR_RIGHT se deve andare a dx,
			//	DIR_CENTRE se Š centrato;

	//		byte testint(byte y,byte terr);		// linea y di test
	//		byte testbottom(byte terr);			// livello dei piedi
	//		byte testunder(byte terr,byte pos=0);	// sotto i piedi
	//		byte testtop(byte terr);			// livello della testa
	//		byte testover(byte terr,byte pos=0);	// sopra la testa


			//	ritorna 0 se non Š centrato, 1 se Š centrato
			//bool centreint(byte y,byte terr);	// linea y di test
			//bool centrebottom(byte terr);
			//bool centretop(byte terr);

////////////////////////////////////////////////////////////////////////


////////////////// MOVIMENTO DEL PERSONAGGIO (PLATFORM) ////////////////


		/////	Queste funzioni impostano il movimento del personaggio,
		//			ritornano 0 se il personaggio non pu• compiere
		//			quel movimento, altrimenti 1.

			byte setmove(byte dir);		//sinistra o destra?
			byte resmove(void);

			byte setrun(void);
			byte resrun(void);

			byte setcrouch(void);
			byte rescrouch(void);

			byte setgraspcl(byte dir);
			byte resgraspcl(void);

			byte setgraspst(byte dir);
			byte resgraspst(void);

			byte setclimb(byte dir);	// su o gi—?
			byte resclimb(void);

			byte setstairs(byte dir);  // su o gi—?-sinistra o destra?
			byte resstairs(void);

			byte setjump(void);


		// Funzione che fa compiere al personaggio gli effettivi
		//	movimenti (forse anche quelli grafici :) )

			byte moveplatform(void);

////////////////////////////////////////////////////////////////////////

		};

#include"D:\djgpp\game01\ClChar.cpp"
//#include"D:\djgpp\game01\ClMove.cpp"

#endif
