
#ifndef CLTEXTURE_HPP
#define CLTEXTURE_HPP

#include<allegro.h>
#include<default.h>

	//  Alcune costanti devono essere esterne:
	//	-   UNITX	=
	//	-	UNITY	=
/*
const int NTOTALTEXT=NXTEXTFILE*NYTEXTFILE;	// Numero complessivo di
										// texture.
const int XTEXTFILE=NXTEXTFILE*UNITX;	// Larghezza del blocco delle
										// texture in pixel...
const int YTEXTFILE=NYTEXTFILE*UNITY;	// ... e l'altezza.
 */


// A questa classe gli viene passato solo una BITMAP che contiene le
// texture: meno ne sa meglio Š! :)

class T_Texture{

		private:

			int NXTEXTFILE;		//	N. di texture in larghezza
			int NYTEXTFILE;		//  N. di texture in altezza
			int NTOTALTEXT;		// Numero complessivo di
								// texture.
			int XTEXTFILE;		// Larghezza del blocco delle
								// texture in pixel...
			int YTEXTFILE;

			BITMAP *global;
			BITMAP **texture;

			//IndexTexture *FileIndice;

		public:

			T_Texture(void);
			~T_Texture(void);


			void InitTexture(int textx,int texty);
							// textx: numero texture in larghezza
							// texty: numero texture in altezza

			//byte SetIndexFile(char *nome);

			byte LoadTexture(BITMAP *source);

			//void LoadTexture(byte nset);	// Carica le texture dal file
						// indicato nel file indice con il numero nset.
						// Sar… usato per i datafile. NO!!!! Questa classe
						// Riceve solo un BITMAP!


			//void OutTexture(BITMAP *out,int x,int y,byte code);
			void OutTexture(BITMAP *out);

			///////////// FUNZIONI DI MANUTENZIONE //////////////////

			void RetTotalBmp(BITMAP *tmp);

		};

#include"D:\djgpp\game01\ClTextur.cpp"

#endif
