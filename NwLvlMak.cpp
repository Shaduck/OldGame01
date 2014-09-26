#include<allegro.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>


typedef unsigned char byte;

#include"Costanti.cpp"
#include"Common.hpp"


const int BIGUNITX=16;				// Dimensione del cursore a dimensione
const int BIGUNITY=16;				// raddoppiata


const byte MAX_TERR=9;
const byte MAX_SOLID=2;

///////////////// COSTANTI  DEGLI  OGGETTI  A  VIDEO /////////////////////

/////////////////// CONTATORE DEI LIVELLI DELLA MAPPA //////////////

int MAPCOUNTBARX=0;
int MAPCOUNTBARY=0;
int MAPCOUNTLARGH=100;
int MAPCOUNTALT=10;

//////////////////////////////////////////////////////////////////

////////////////////// FINESTRA PRINCIPALE ///////////////////////

// Dimensione delle texture nell'editor
const int MUNITX=5;								//  20	12	10
const int MUNITY=MUNITX;	  			//	16	10	 8

const int XLAR=MUNITX*NSPRITEX;		// Larghezza della schermata dell'editor
const int YLAR=MUNITY*NSPRITEY;		// della mappa

int MAINWINDX=0;
int MAINWINDY=10;
int MAINWINDLARGH=XLAR;		//200;
int MAINWINDALT=YLAR;		//150;

///////////////////////////////////////////////////////////////////

////////////////////////// FINESTRA LATERALE //////////////////////

int MINIWINDX=280;
int MINIWINDY=10;
int MINIWINDLARGH=WIMGX*UNITX;	//40;
int MINIWINDALT=WIMGY*UNITY;	//40;

const byte WIMGOFFX=2;				// Numero di unit‡ a dx e a sx di quella
									// centrale nella finestra a grandezza
									// naturale.
const byte WIMGOFFY=2;				// Numero di unit‡ in alto e in basso
const byte WIMGX=(WIMGOFFX*2)+1;	// Larghezza e altezza complessiva in
const byte WIMGY=(WIMGOFFY*2)+1;	// numero di unit‡
const byte NWINDIMG=WIMGX*WIMGY;	// Numero di blocchi
//byte windimg[WIMGY][WIMGX];			// matrice della finestra

///////////////////////////////////////////////////////////////////

////////////////////// BARRA DELLE TEXTURE ////////////////////////

int NBARTEXT=18;
int TEXTBAR1X=0;
int TEXTBAR1Y=224;
int TEXTBAR1LARGH=(NBARTEXT+2)*UNITX;
int TEXTBAR1ALT=UNITY*2;

int TEXTBAR2X=160;
int TEXTBAR2Y=224;
int TEXTBAR1LARGH=160;
int TEXTBAR1ALT=16;

///////////////////////////////////////////////////////////////////

/////////////// VARIABILI DI CONTROLLO ////////////////////////////
/////////////// DEGLI OGGETTI A VIDEO  ////////////////////////////

T_Level livello;

byte mainwind[NSPRITEY][NSPRITEX];
int cursorx=0,cursory=0;

byte miniwmask[WIMGY][WIMGX];

byte spritemask1[2][18];
int currenttile1;

byte spritemask2[2][18];
int currenttile2;

/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#include"ClMap.hpp"

byte CURS_COL=7;
byte CONF_COL=3;
byte BACKG_COL=5;
byte DESK_COL=0;

void GameInit(void)
{

	allegro_init();
   	install_keyboard();
   	install_timer();
	install_mouse();
	clear_keybuf();

   	set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0);
   	set_pallete(desktop_pallete);

	return;
}


/************************************************************************
*			Sottoprogramma per la distruzione dell'ambiente				*
************************************************************************/

	// Evidentemente non fa parte del WWF

void GameExit(void)
{

	remove_keyboard();
	remove_timer();
	remove_mouse();

	allegro_exit();

 	return;
}

void ImpostaTexture(int NumText)
{

	blit(mappa.RetTextBmp(NumText),textures,0,0,0,0,128,128);

}

//////////// Disegno dello schermo principale /////////////////////

void DrawMainWindow(void)
{

	rectfill(buffer,MAINWINDX,MAINWINDY,MAINWINDLARGH,
									MAINWINDALT,BACKG_COL);

	for(i=0,y=0,k=0;i<NSPRITEY;i++,y+=MUNITY){
		for(j=0,x=0;j<NSPRITEX;j++,x+=MUNITX,k++){
			stretch_blit(sprites[livello.retsprite(k)],
						buffer,0,0,UNITX,UNITY,x,y,MUNITX,MUNITY);
		}
	}

	rect(buffer,cursorx,cursory,cursorx+MUNITX-1,cursory+MUNITY-1,
											CURS_COL);
	return;
}

//////////////// Disegno della finestra laterale //////////////////

void DrawMiniWindow(void)
{

	for(i=0,y=MINIWINDY;i<WIMGY;i++,y+=UNITY){
		for(j=0,x=MINIWINDX;j<WIMGX;j++,x+=UNITX){
			blit(sprites[windimg[i][j]],buffer,0,0,x,y,UNITX,UNITY);
		}
	}
	return;
}

/////////////// Disegno elenco sprite ///////////////////

void DrawTileLists(void)
{

	for(i=0,y=TEXTBAR1Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR1X;j<20;j++,x+=UNITX){
			blit(sprites[spritemask1[i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

	rect(buffer,160,199,160+BIGUNITX,200+BIGUNITY,CURS_COL);

/////////////// Disegno elenco sprite numero 2 ///////////////////

	for(i=0,y=TEXTBAR2Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR2X;j<20;j++,x+=UNITX){
			blit(sprites[spritemask2[i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

	rect(buffer,160,199,160+BIGUNITX,200+BIGUNITY,CURS_COL);

	return;
}

int main(void)
{

	int i,j,k,x,y;
	//byte bi,bj;
	//byte cursize=1;

	//int cursorx=0,cursory=0;

	//byte spritecont=10,spritecont2=10+16;
	//byte sprconmeno,sprconpiu;
	//byte sprconmeno2,sprconpiu2;

	//byte terrancont=0,solidcont=0;

	//bool speed=false;
	//bool print=false,toggleprint=false;
	//bool moved=false,pushed=false;

	int nlevel;

	BITMAP *buffer;				//	Double-buffering
	BITMAP *textures;			//	Immagine globale delle texture
	BITMAP *sprites[256];		// 	Array degli sprite
	//RGB color[256];

	//char nomefile[30],errmess[20];
	//FILE *fp;


	T_Map mappa;


	strcpy(errmess,"");		// inizializzo la stringa

	if(!mappa.InitLevel()){
		strcpy(errmess,"Impossibile allocare la mappa");
		exit(0);
	}

	/////////// INPUT NOME FILE DELLA MAPPA   ///////////////////////
	printf("\n\t Inserta il nome del file della mappa(senza est.) : ");
	gets(nomefile);
	strcat(nomefile,".map");
	/////////////////////////////////////////////////////////////////

	if(!mappa.SetMapFile){
		printf("\n\t File non trovato");
	}

	nlevel=mappa.RetNLevel();

	printf("\n\t Numero attuale di livelli: %d",nlevel);
	printf("\n\t Inserta il numero di livelli da creare nella mappa:");
	printf("\n\t (0 per non aggiungerne)");
	scanf("%d",&i);
	if(i>0){
		nlevel+=i;
		mappa.SetNLevel(nlevel);
		mappa.AllocMap();
	}

	GameInit();

	textures=create_bitmap(128,128);

	mappa.SetTextureFile("D:\\DJGPP\\Game01\\IndexTxt.txt");

/////// Gestione delle texture... sç, lo so, lo so che sono tile
	for(y=0,i=0;y<16&&i<256;y++){
		for(x=0;x<16&&i<256;x++,i++){
			sprites[i]=create_sub_bitmap(textures,x*UNITX,
								y*UNITY,UNITX,UNITY);
		}
	}


/////////// INIZIALIZZAZIONE MATRICE DELLA FINESTRELLA /////
	for(i=0;i<WIMGY;i++){
		for(j=0;j<WIMGX;j++){
			miniwmask[i][j]=0;
		}
	}

////// INIZIALIZZAZIONE MATRICE DELLA LISTA DELLE TILE/////////////

	for(i=0;i<2;i++){
		for(j=0;j<20;j++){
			spritemask1[i][j]=0;
			spritemask2[i][j]=0;
		}
	}

///////////////// BUFFER PER IL DOUBLE BUFFERING //////////////

	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	//show_mouse(buffer);

	clear_to_color(buffer,DESK_COL);
	//clear_to_color(lvldis,BACKG_COL);

//////////////////////////////////////////////////////////////////


/////////////////////////// PUTTAGGIO  ///////////////////////////

	DrawMainWindow();
	DrawMiniWindow();
	DrawTileLists();

	//show_mouse(buffer);

	blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	//rectfill(screen,0,0,100,100,5);

//////////////////////////////////////////////////////////////////

////////////////// INPUT E CONTROLLI  ////////////////////////////

	while(!key[KEY_ESC]){

		if(key[KEY_RSHIFT]||key[KEY_LSHIFT]){
			speed=true;
		}else{
			speed=false;
		}
		if(key[KEY_P]){
			cursize=2;
			moved=true;
		}
		if(key[KEY_O]){
			cursize=1;
			moved=true;
		}

		if(key[KEY_SPACE]&&!pushed){
		 	print=true;
			pushed=true;
			moved=true;
		}

		if(key[KEY_T]&&!pushed){
			pushed=true;
			moved=true;
			if(toggleprint){
				toggleprint=false;
			}else{
				toggleprint=true;
			}
		}

		if(key[KEY_LEFT]&&cursorx&&!pushed){
			if(!speed)
				pushed=true;
			cursorx--;
			if(cursize==2&&cursorx)
				cursorx--;
			relx=cursorx*MUNITX;
			moved=true;
		}
		if(key[KEY_RIGHT]&&cursorx<NSPRITEX-cursize&&!pushed){
			if(!speed)
				pushed=true;
			cursorx++;
			if(cursize==2&&cursorx<NSPRITEX-cursize)
				cursorx++;
			relx=cursorx*MUNITX;
			moved=true;
		}
		if(key[KEY_UP]&&cursory&&!pushed){
			if(!speed)
				pushed=true;
			cursory--;
			if(cursize==2&&cursory)
				cursory--;
			rely=cursory*MUNITY;
			moved=true;
		}
		if(key[KEY_DOWN]&&cursory<NSPRITEY-cursize&&!pushed){
			if(!speed)
				pushed=true;
			cursory++;
			if(cursize==2&&cursory<NSPRITEY-cursize)
				cursory++;
			rely=cursory*MUNITY;
			moved=true;
		}

		if(key[KEY_PLUS_PAD]&&!pushed){
			//if(!button[KEY_PLUS_PAD]){
			pushed=true;
			BACKG_COL++;
			moved=true;
			//button[KEY_PLUS_PAD]=true;
			//}
		//}else{
		//	button[KEY_PLUS_PAD]=false;
		}
		if(key[KEY_Z]&&!pushed){
			if(!speed)
				pushed=true;

			//spritecont--;
			//spritecont2--;
			//relx=cursorx*MUNITX;
			moved=true;
		}
		if(key[KEY_X]&&!pushed){
			if(!speed)
				pushed=true;
			//spritecont++;
			//spritecont2++;
			//relx=cursorx*MUNITX;
			moved=true;
		}

		if(key[KEY_A]&&!pushed){
			if(!speed)
				pushed=true;
			if(terrancont>0)
				terrancont--;
			else
				terrancont=MAX_TERR;
			//spritecont2++;
			//relx=cursorx*MUNITX;
			moved=true;
		}
		if(key[KEY_S]&&!pushed){
			if(!speed)
				pushed=true;

			terrancont++;
			if(terrancont>MAX_TERR)
				terrancont=0;
			//spritecont2++;
			//relx=cursorx*MUNITX;
			moved=true;
		}

		if(key[KEY_Q]&&!pushed){
			if(!speed)
				pushed=true;
			if(solidcont>0)
				solidcont--;
			else
				solidcont=MAX_SOLID;
			//spritecont2++;
			//relx=cursorx*MUNITX;
			moved=true;
		}
		if(key[KEY_W]&&!pushed){
			if(!speed)
				pushed=true;

			solidcont++;
			if(solidcont>MAX_SOLID)
				solidcont=0;
			//spritecont2++;
			//relx=cursorx*MUNITX;
			moved=true;
		}

		if(key[KEY_F3]&&!pushed){
			pushed=true;

			fp=fopen(nomefile,"rb");
			if(fp!=NULL){
				if(!mappa.LoadLevel(fp))
					strcpy(errmess,"Unable to load");
				fclose(fp);

				for(i=0,k=0;i<NSPRITEY;i++){
					for(j=0;j<NSPRITEX;j++,k++){
						livello[i][j].solid=mappa.RetSolid(k);
						livello[i][j].terran=mappa.RetTerran(k);
					}
				}

			}

			moved=true;
		}

		if(key[KEY_F2]&&!pushed){
			pushed=true;

			/*
			for(i=0,k=0;i<NSPRITEY;i++){
					for(j=0;j<NSPRITEX;j++,k++){
					mappa.SetSolid(k,livello[i][j].solid);
					mappa.SetTerran(k,livello[i][j].terran);
				}
			}

			for(i=OVER_SPACE,k=0;i<OVER_SPACE+NSPRITEY;i++){
					for(j=LEFT_SPACE;j<LEFT_SPACE+NSPRITEX;j++,k++){
					mappa.SetSprite(k,livello[i][j].sprite);
				}
			}
			*/

			fp=fopen(nomefile,"wb");

			//mappa.SaveLevel(fp);

			fclose(fp);
		}

		if(key[KEY_F7]&&!pushed){
			pushed=true;

			for(i=0,k=0;i<NSPRITEY;i++){
				for(j=0;j<NSPRITEX;j++,k++){
					//fwrite(&livello[i][j],sizeof(level),1,fp);
					livello[i][j].solid=mappa.RetSolid(k);
					livello[i][j].terran=mappa.RetTerran(k);
				}
			}

			moved=true;
		}

		if(key[KEY_F5]&&!pushed){
			pushed=true;

			for(i=0,k=0;i<NSPRITEY;i++){
					for(j=0;j<NSPRITEX;j++,k++){
					mappa.SetSolid(k,livello[i][j].solid);
					mappa.SetTerran(k,livello[i][j].terran);
				}
			}

		}

		if(key[KEY_ENTER]){
			clear_to_color(buffer,0);
			for(i=OVER_SPACE,y=0;i<NSPRITEY-BOTTOM_SPACE;i++,y+=UNITY){
				for(j=LEFT_SPACE,x=0;j<NSPRITEX-RIGHT_SPACE;j++,x+=UNITX){
					blit(sprites[livello[i][j].sprite],buffer,0,0,
							x,y,UNITX,UNITY);
				}
			}
			vsync();
			blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

			while(!key[KEY_BACKSPACE]);
			moved=true;
		}

		if(print||toggleprint){
			livello[cursory][cursorx].sprite=spritecont;
			livello[cursory][cursorx].terran=terrancont;
			livello[cursory][cursorx].solid=solidcont;

			print=false;
			//stretch_blit(sprites[spritecont],lvldis,0,0,UNITX,UNITY,
			//				cursorx*MUNITX,cursory*MUNITY,MUNITX,MUNITY);
			if(cursize>1){
					livello[cursory][cursorx+1].sprite=spritecont+1;
					livello[cursory][cursorx+1].terran=terrancont;
					livello[cursory][cursorx+1].solid=solidcont;
			//		stretch_blit(sprites[spritecont+1],
			//					lvldis,0,0,UNITX,UNITY,(cursorx+1)*MUNITX,
			//								cursory*MUNITY,MUNITX,MUNITY);

					livello[cursory+1][cursorx].sprite=spritecont2;
					livello[cursory+1][cursorx].terran=terrancont;
					livello[cursory+1][cursorx].solid=solidcont;
			//		stretch_blit(sprites[spritecont2],
			//					lvldis,0,0,UNITX,UNITY,cursorx*MUNITX,
			//								(cursory+1)*MUNITY,MUNITX,MUNITY);

					livello[cursory+1][cursorx+1].sprite=spritecont2+1;
					livello[cursory+1][cursorx+1].terran=terrancont;
					livello[cursory+1][cursorx+1].solid=solidcont;
			//		stretch_blit(sprites[spritecont2+1],
			//					lvldis,0,0,UNITX,UNITY,(cursorx+1)*MUNITX,
			//								(cursory+1)*MUNITY,MUNITX,MUNITY);

			}
		}

		if(moved){
			clear_to_color(buffer,DESK_COL);


				// 	Puttaggio dello schema del livello : ex lvldis
			rectfill(buffer,0,0,XLAR,YLAR,BACKG_COL);
			//blit(lvldis,buffer,0,0,0,0,XLAR,YLAR);
			for(i=0,y=0;i<NSPRITEY;i++,y+=MUNITY){
				for(j=0,x=0;j<NSPRITEX;j++,x+=MUNITX){
					if(livello[i][j].sprite){
						stretch_blit(sprites[livello[i][j].sprite],
							buffer,0,0,UNITX,UNITY,x,y,MUNITX,MUNITY);
					}
				}
			}

				// Rettangoli dello schema

			//rect(buffer,LEFT_SPACE*MUNITX,OVER_SPACE*MUNITY,
			//	XLAR-(RIGHT_SPACE*MUNITX)-1,YLAR-(BOTTOM_SPACE*MUNITY)-1,
			//												CONF_COL);

			rect(buffer,relx,rely,relx+(cursize*MUNITX-1),
									rely+(cursize*MUNITY-1),CURS_COL);

				// Disegno della finestra laterale //
			for(i=cursory-2,bi=0;i<cursory+3;i++,bi++){
				for(j=cursorx-2,bj=0;j<cursorx+3;j++,bj++){
			 		if(i<0||j<0){
						windimg[bi][bj]=0;
					}else{
						windimg[bi][bj]=livello[i][j].sprite;
					}
				}
			}

			for(i=0,y=0;i<WIMGY;i++,y+=UNITY){
				for(j=0,x=SCREEN_W-(WIMGX*UNITX);j<WIMGX;j++,x+=UNITX){
					//temp=;
					blit(sprites[windimg[i][j]],buffer,0,0,x,y,UNITX,UNITY);
				}
			}

				// Se ä premuto 'toggleprint' ( che ä un Pokemon? )
			if(toggleprint){
				rectfill(buffer,300,110,320,130,CURS_COL);
			}else{
				rectfill(buffer,300,110,320,130,DESK_COL);
			}

			textprintf(buffer,font,250,60,255,"Sol : %d",solidcont);
			textprintf(buffer,font,250,70,255,"Terr: %d",terrancont);

				// Disegno elenco sprite
			if(spritecont>10){
				sprconmeno=spritecont-10;
			}else{
			 	sprconmeno=256-(10-spritecont);
			}
			if(spritecont<246){
				sprconpiu=spritecont+10;
			}else{
			 	sprconpiu=10-(256-spritecont);
			}
			if(spritecont2>10){
				sprconmeno2=spritecont2-10;
			}else{
			 	sprconmeno2=256-(10-spritecont2);
			}
			if(spritecont2<246){
				sprconpiu2=spritecont2+10;
			}else{
			 	sprconpiu2=10-(256-spritecont2);
			}

			for(bi=sprconmeno,bj=sprconmeno2,x=0;bi!=sprconpiu;bi++,bj++,x+=BIGUNITX){
				stretch_blit(sprites[bi],buffer,0,0,UNITX,UNITY,x,
						200,BIGUNITX,BIGUNITY);
				if(cursize>1){
					stretch_blit(sprites[bj],buffer,0,0,
						UNITX,UNITY,x,216,BIGUNITX,BIGUNITY);
				}
			}
			rect(buffer,160,199,160+(cursize*BIGUNITX),
									200+(cursize*BIGUNITY),CURS_COL);

			moved=false;
		}

		if(pushed){
			pushed=false;
			for(i=0;i<128;i++){
				if(key[i]){
					pushed=true;
					break;
				}
			}
		}

		show_mouse(buffer);
		vsync();
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		show_mouse(NULL);
	}

		/// Distruzione Bitmap

	for(i=0;i<256;i++){
		destroy_bitmap(sprites[i]);
		//destroy_bitmap(texture[1][i]);
	}

	destroy_bitmap(textures);
	//destroy_bitmap(lvldis);
	destroy_bitmap(buffer);

	readkey();
	GameExit();

	printf("Programmed with DJGPP RHIDE Allegro");

	puts(errmess);

	getch();


	return 0;

}
