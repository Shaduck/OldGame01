
#ifndef CLLEVEL_HPP
#define CLLEVEL_HPP

#include<allegro.h>
#include<default.h>


	//  Alcune costanti devono essere esterne:
	//	-	NSPRITEX	= 	Larghezza in blocchi della mappa
	//	-	NSPRITEY	=	Altezza in blocchi della mappa

// Campo di bit che contiene solidit… e tipo di terreno.
			struct Levelst1{
				byte solid 		:	4;
				byte terran 	:	4;
				//byte sprite	:	8;
			};


//const int LEVELSIZE=(sizeof(Levelst1)*MASKTOT)+
//					(sizeof(byte)*SPRITETOT)+
//					(sizeof(int)*4);
										// Grandezza in byte di una mappa

class T_Level{


			byte *sprite;
			Levelst1 *map;

			//int next[4];

		public:

			T_Level(void);
			~T_Level(void);

			//////////////  FUNZIONI PER IL GIOCO  //////////////////////

			bool InitLevel(void);

			bool LoadLevel(FILE *fp);
				//bool LoadOldLevel(FILE *fp);
				//bool LoadNextLevel(FILE *fp);

				//bool SaveOldLevel(FILE *fp);
				//bool SaveNextLevel(FILE *fp);

			/*
			byte OutCenterLevel(byte **mskterr,byte **msksolid,
													byte *msktext);
			byte OutBordLevel(byte dir,byte **mskterr,byte **msksolid);
			*/
			byte OutCenterLevel(void);
			byte OutBordLevel(byte dir);

			//////////////////// FUNZIONI PER LA MANUTENZIONE  ///////////

			byte RetSolid(int x);
			byte RetTerran(int x);
			byte RetSprite(int x);

			void SetSolid(int x,byte val);
			void SetTerran(int x,byte val);
			void SetSprite(int x,byte val);

			bool SaveLevel(FILE *fp);

			bool InsertLevel(T_Level &Livello);

			//byte RetNextLev(byte dir);

		};

#include"D:\djgpp\game01\ClLevel.cpp"

#endif
