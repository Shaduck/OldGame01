#include<allegro.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

/*
///////////////////////////////////////////////////////////////////////
			Ma il file dei livelli come Š fatto?
			( Concezione vecchia, ma non proprio da buttare ;) )

	byte tipo sprite;
	level livello[44][36] (vedi sotto)
	Enemy [10] (Propriet… dei nemici del livello: coord di partenza,ecc.
				Forse stessa struct delle persone: cosa dicono)
	Object[10] (Propriet… degli oggetti del livello: porte,interruttori,
					prob fanno riferimento ad un vettore di n
					elem.(flag): se un flag Š settato, la porta Š aperta
					se premi un interruttore o se hai degli oggetti si
					setta un flag)

///////////////////////////////////////////////////////////////////////
*/



typedef unsigned char byte;

struct level{
		byte solid	; //	:	4;
		byte terran; //	:	4;
		byte sprite; //	:	8;
		};					// 	:)

//byte *sprite;

#include"D:\Djgpp\Game01\Costanti.cpp"
#include"D:\Djgpp\Game01\Common.hpp"

/*
const int LEFT_SPACE=5;
const int OVER_SPACE=5;
const int RIGHT_SPACE=5;
const int BOTTOM_SPACE=5;

const int RESOLUTION_X=320;
const int RESOLUTION_Y=240;
*/

const int MUNITX=5;								//  20	12	10
const int MUNITY=MUNITX;	  			//	16	10	 8


/*
const int UNITX=8;
const int UNITY=8;

const int NSPRITEX=(int)(RESOLUTION_X/UNITX);	//	40
const int NSPRITEY=(int)(RESOLUTION_Y/UNITY);	//	30
const int SPRITETOT=NSPRITEX*NSPRITEY;	//Numero totale degli sprite
										// effettivamente visibili.

const int MASKX=40+LEFT_SPACE+RIGHT_SPACE; 	// 	16	26	32	50
const int MASKY=30+OVER_SPACE+BOTTOM_SPACE;	//				40
const int MASKTOT=MASKX*MASKY;			//Numero complessivo dei blocchi
*/

const int XLAR=MUNITX*NSPRITEX;
const int YLAR=MUNITY*NSPRITEY;

const int BIGUNITX=16;
const int BIGUNITY=16;

const byte WIMGOFFX=2;
const byte WIMGOFFY=2;
const byte WIMGX=(WIMGOFFX*2)+1;
const byte WIMGY=(WIMGOFFY*2)+1;
const byte NWINDIMG=WIMGX*WIMGY;
byte windimg[WIMGY][WIMGX];

const byte MAX_TERR=9;
const byte MAX_SOLID=2;

#include"D:\Djgpp\Game01\ClMap.hpp"

//BITMAP *allsolid;
//BITMAP *semisolid;
//BITMAP *nosolid;

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

void Init_Texture(void)
{
 	//allsolid=

	return;
}

int main(void)
{
	int i,j,k,x,y;
	byte bi,bj;
	byte cursize=1;

	int contx=0,conty=0;
	int relx=0,rely=0;
	byte spritecont=10,spritecont2=10+16;
	byte sprconmeno,sprconpiu;
	byte sprconmeno2,sprconpiu2;

	byte terrancont=0,solidcont=0;

	bool speed=false;
	bool print=false,toggleprint=false;
	bool moved=false,pushed=false;

	//bool button[128];

	BITMAP *buffer;//*lvldis,*buffer;
	BITMAP *textures;
	//BITMAP *texture[2][20];
	BITMAP *sprites[256];
	RGB color[256];

	char nomefile[30],errmess[20];
	FILE *fp;

	level livello[MASKY][MASKX];

	T_Level mappa;

	strcpy(errmess,"");

	if(!mappa.InitLevel())
		strcpy(errmess,"Impossibile allocare la mappa");

	//printf("%ld",sizeof(BITMAP));
	//getch();


	printf("\n\t Inserta il nome del file da creare(senza est.) : ");
	gets(nomefile);
	strcat(nomefile,".map");

	//fp=fopen(nomefile,"w"))


	for(i=0;i<MASKY;i++){
		for(j=0;j<MASKX;j++){
			livello[i][j].solid=0;
			livello[i][j].terran=0;
			livello[i][j].sprite=0;
		}
	}

	GameInit();

	textures=create_bitmap(128,128);
	textures=load_bmp("D:\\DJGPP\\Game01\\Moveto.bmp",color);
	//textures=load_bmp("Moveto.bmp",color);

	if(!textures){
		GameExit();
		printf("ERRORE Grande come una casa!");
		getch();

		exit(0);
	}

	for(y=0,i=0;y<16&&i<256;y++){
		for(x=0;x<16&&i<256;x++,i++){
			sprites[i]=create_sub_bitmap(textures,x*UNITX,
								y*UNITY,UNITX,UNITY);
			//texture[1][i]=create_sub_bitmap(textures,x*UNITX,
			//					(y+1)*UNITY,UNITX,UNITY);
		}
	}

	for(i=0;i<WIMGY;i++){
		for(j=0;j<WIMGX;j++){
			windimg[i][j]=0;
			//clear_to_color(windimg[i][j],BACKG_COL);
		}
	}

	//lvldis=create_bitmap(XLAR,YLAR);
	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	//show_mouse(buffer);

	clear_to_color(buffer,DESK_COL);
	//clear_to_color(lvldis,BACKG_COL);

	set_palette(color);

		// Disegno dello schermo principale //
	rectfill(buffer,0,0,XLAR,YLAR,BACKG_COL);
	//blit(lvldis,buffer,0,0,0,0,XLAR,YLAR);
	//rect(buffer,LEFT_SPACE*MUNITX,OVER_SPACE*MUNITY,
	//		XLAR-(RIGHT_SPACE*MUNITX)-1,YLAR-(BOTTOM_SPACE*MUNITY)-1,CONF_COL);

	rect(buffer,relx,rely,relx+MUNITX-1,rely+MUNITY-1,CURS_COL);

		// Disegno della finestra laterale //

	for(i=0,y=0;i<WIMGY;i++,y+=UNITY){
		for(j=0,x=SCREEN_W-(WIMGX*UNITX);j<WIMGX;j++,x+=UNITX){
			blit(sprites[windimg[i][j]],buffer,0,0,x,y,UNITX,UNITY);
		}
	}

	textprintf(buffer,font,250,60,255,"Sol : %d",solidcont);
	textprintf(buffer,font,250,70,255,"Terr: %d",terrancont);

		// Disegno elenco sprite

	for(bi=0,x=0;bi<20;bi++,x+=BIGUNITX){
		stretch_blit(sprites[bi],buffer,0,0,UNITX,UNITY,x,
						200,BIGUNITX,BIGUNITY);
	}
	rect(buffer,160,199,160+BIGUNITX,200+BIGUNITY,CURS_COL);

	//show_mouse(buffer);

	blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	//rectfill(screen,0,0,100,100,5);

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

		if(key[KEY_LEFT]&&contx&&!pushed){
			if(!speed)
				pushed=true;
			contx--;
			if(cursize==2&&contx)
				contx--;
			relx=contx*MUNITX;
			moved=true;
		}
		if(key[KEY_RIGHT]&&contx<MASKX-cursize&&!pushed){
			if(!speed)
				pushed=true;
			contx++;
			if(cursize==2&&contx<MASKX-cursize)
				contx++;
			relx=contx*MUNITX;
			moved=true;
		}
		if(key[KEY_UP]&&conty&&!pushed){
			if(!speed)
				pushed=true;
			conty--;
			if(cursize==2&&conty)
				conty--;
			rely=conty*MUNITY;
			moved=true;
		}
		if(key[KEY_DOWN]&&conty<MASKY-cursize&&!pushed){
			if(!speed)
				pushed=true;
			conty++;
			if(cursize==2&&conty<MASKY-cursize)
				conty++;
			rely=conty*MUNITY;
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
			spritecont--;
			spritecont2--;
			//relx=contx*MUNITX;
			moved=true;
		}
		if(key[KEY_X]&&!pushed){
			if(!speed)
				pushed=true;
			spritecont++;
			spritecont2++;
			//relx=contx*MUNITX;
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
			//relx=contx*MUNITX;
			moved=true;
		}
		if(key[KEY_S]&&!pushed){
			if(!speed)
				pushed=true;

			terrancont++;
			if(terrancont>MAX_TERR)
				terrancont=0;
			//spritecont2++;
			//relx=contx*MUNITX;
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
			//relx=contx*MUNITX;
			moved=true;
		}
		if(key[KEY_W]&&!pushed){
			if(!speed)
				pushed=true;

			solidcont++;
			if(solidcont>MAX_SOLID)
				solidcont=0;
			//spritecont2++;
			//relx=contx*MUNITX;
			moved=true;
		}

		if(key[KEY_F3]&&!pushed){
			pushed=true;

			fp=fopen(nomefile,"rb");
			if(fp!=NULL){
				if(!mappa.LoadLevel(fp))
					strcpy(errmess,"Unable to load");
				fclose(fp);

				for(i=0,k=0;i<MASKY;i++){
					for(j=0;j<MASKX;j++,k++){
						//fwrite(&livello[i][j],sizeof(level),1,fp);
						livello[i][j].solid=mappa.RetSolid(k);
						livello[i][j].terran=mappa.RetTerran(k);
					}
				}

				for(i=OVER_SPACE,k=0;i<OVER_SPACE+NSPRITEY;i++){
					for(j=LEFT_SPACE;j<LEFT_SPACE+NSPRITEX;j++,k++){
						//fwrite(&livello[i][j],sizeof(level),1,fp);
						livello[i][j].sprite=mappa.RetSprite(k);
						//mappa.SetTerran(i*MASKX+j,livello[i][j].terran);
					}
				}
			}

			moved=true;
		}

		if(key[KEY_F2]&&!pushed){
			pushed=true;

			/*
			for(i=0,k=0;i<MASKY;i++){
					for(j=0;j<MASKX;j++,k++){
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

			for(i=0,k=0;i<MASKY;i++){
				for(j=0;j<MASKX;j++,k++){
					//fwrite(&livello[i][j],sizeof(level),1,fp);
					livello[i][j].solid=mappa.RetSolid(k);
					livello[i][j].terran=mappa.RetTerran(k);
				}
			}

			for(i=OVER_SPACE,k=0;i<OVER_SPACE+NSPRITEY;i++){
				for(j=LEFT_SPACE;j<LEFT_SPACE+NSPRITEX;j++,k++){
					//fwrite(&livello[i][j],sizeof(level),1,fp);
					livello[i][j].sprite=mappa.RetSprite(k);
					//mappa.SetTerran(i*MASKX+j,livello[i][j].terran);
				}
			}

			moved=true;
		}

		if(key[KEY_F5]&&!pushed){
			pushed=true;

			for(i=0,k=0;i<MASKY;i++){
					for(j=0;j<MASKX;j++,k++){
					mappa.SetSolid(k,livello[i][j].solid);
					mappa.SetTerran(k,livello[i][j].terran);
				}
			}

			for(i=OVER_SPACE,k=0;i<OVER_SPACE+NSPRITEY;i++){
					for(j=LEFT_SPACE;j<LEFT_SPACE+NSPRITEX;j++,k++){
						mappa.SetSprite(k,livello[i][j].sprite);
				}
			}

		}

		if(key[KEY_ENTER]){
			clear_to_color(buffer,0);
			for(i=OVER_SPACE,y=0;i<MASKY-BOTTOM_SPACE;i++,y+=UNITY){
				for(j=LEFT_SPACE,x=0;j<MASKX-RIGHT_SPACE;j++,x+=UNITX){
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
			livello[conty][contx].sprite=spritecont;
			livello[conty][contx].terran=terrancont;
			livello[conty][contx].solid=solidcont;

			print=false;
			//stretch_blit(sprites[spritecont],lvldis,0,0,UNITX,UNITY,
			//				contx*MUNITX,conty*MUNITY,MUNITX,MUNITY);
			if(cursize>1){
					livello[conty][contx+1].sprite=spritecont+1;
					livello[conty][contx+1].terran=terrancont;
					livello[conty][contx+1].solid=solidcont;
			//		stretch_blit(sprites[spritecont+1],
			//					lvldis,0,0,UNITX,UNITY,(contx+1)*MUNITX,
			//								conty*MUNITY,MUNITX,MUNITY);

					livello[conty+1][contx].sprite=spritecont2;
					livello[conty+1][contx].terran=terrancont;
					livello[conty+1][contx].solid=solidcont;
			//		stretch_blit(sprites[spritecont2],
			//					lvldis,0,0,UNITX,UNITY,contx*MUNITX,
			//								(conty+1)*MUNITY,MUNITX,MUNITY);

					livello[conty+1][contx+1].sprite=spritecont2+1;
					livello[conty+1][contx+1].terran=terrancont;
					livello[conty+1][contx+1].solid=solidcont;
			//		stretch_blit(sprites[spritecont2+1],
			//					lvldis,0,0,UNITX,UNITY,(contx+1)*MUNITX,
			//								(conty+1)*MUNITY,MUNITX,MUNITY);

			}
		}

		if(moved){
			clear_to_color(buffer,DESK_COL);


				// 	Puttaggio dello schema del livello : ex lvldis
			rectfill(buffer,0,0,XLAR,YLAR,BACKG_COL);
			//blit(lvldis,buffer,0,0,0,0,XLAR,YLAR);
			for(i=0,y=0;i<MASKY;i++,y+=MUNITY){
				for(j=0,x=0;j<MASKX;j++,x+=MUNITX){
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
			for(i=conty-2,bi=0;i<conty+3;i++,bi++){
				for(j=contx-2,bj=0;j<contx+3;j++,bj++){
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

				// Se Š premuto 'toggleprint' ( che Š un Pokemon? )
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

	//getch();

		/// Distruzione Bitmap

	for(i=0;i<256;i++){
		destroy_bitmap(sprites[i]);
		//destroy_bitmap(texture[1][i]);
	}

	//BITMAP *lvldis,*buffer;
	//BITMAP *textures;
	//BITMAP *texture[2][20];
	//BITMAP *sprites[256];
	//RGB *color;

	/*for(i=0;i<WIMGY;i++){
		for(j=0;j<WIMGX;j++){
			destroy_bitmap(windimg[i][j]);
		}
	}  */

	destroy_bitmap(textures);
	//destroy_bitmap(lvldis);
	destroy_bitmap(buffer);

	readkey();
	GameExit();

	printf("Maked with DJGPP RHIDE Allegro");

	puts(errmess);

	getch();

	return 0;
}
