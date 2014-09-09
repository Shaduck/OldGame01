#include<allegro.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

#include"D:\Djgpp\Game01\GmMakDef.cpp"
#include"D:\Djgpp\Game01\GmMakFun.cpp"


int main(void)
{
	int i,j,x,y,k;

	bool speed=false;
	bool print=false,toggleprint=false;
	bool moved=false,pushed=false;

	int nlevel;

	char nomefile[30];
	FILE *fp;

///////////////////////////////////////////////////////////////////

	filelog=fopen("LvlMake.log","w");

	/////////// INPUT NOME FILE DELLA MAPPA   ///////////////////////
	printf("\n\t Inserta il nome del file della mappa(senza est.) : ");
	gets(nomefile);
	strcat(nomefile,".map");

	fp=fopen(nomefile,"r");
	nlevel=0;
	if(!fp){
		printf("\n\t File non trovato");
	}else{
		fread(&nlevel,sizeof(int),1,fp);
	}

	printf("\n\t Numero attuale di livelli: %d",nlevel);
	printf("\n\t Inserta il numero di livelli da creare nella mappa:");
	printf("\n\t (0 per non aggiungerne)");
	scanf("%d",&i);
	if(!i){
		nlevel=0;
	}else{
		nlevel+=i;
	}
	/////////////////////////////////////////////////////////////////
	mappa.SetMapFile(nomefile,nlevel);

	livello.InitLevel();

	GameInit();
	InitMPoints();





	i=mappa.SetTextureFile("bmpdata.dat",1);
	if(i){
		//sprintf(strtemp,"Tile non trovate(%d)",i);
		//fputs("Tile non trovate",filelog);
		fprintf(filelog,"Tile non trovate(%d)",i);
	}

/////// Gestione delle texture... sç, lo so, lo so che sono tile
	textures=create_bitmap(128,128);
	for(y=0,i=0;y<16&&i<256;y++){
		for(x=0;x<16&&i<256;x++,i++){
			sprites[i]=create_sub_bitmap(textures,x*UNITX,
								y*UNITY,UNITX,UNITY);
		}
	}

//////////////////////////////////////////////////////////////////

	sldbmp=create_bitmap(32,8);
	for(i=0;i<4;i++){
		solidimg[i]=create_sub_bitmap(sldbmp,i*UNITX,0,
												UNITX,UNITY);
	}

	sldbmp=load_bmp("D:/Djgpp/Game01/LvlMakSl.bmp",color);

	terbmp=create_bitmap(80,8);
	for(i=0;i<10;i++){
		terrainimg[i]=create_sub_bitmap(terbmp,i*UNITX,0,
												UNITX,UNITY);
	}

	terbmp=load_bmp("D:\\Djgpp\\Game01\\LvlMakTr.bmp",color);

////// INIZIALIZZAZIONE DELLA MATRICE PRINCIPALE  /////////////

	for(i=0;i<NSPRITEY;i++){
		for(j=0;j<NSPRITEX;j++){
			mainwind[i][j]=0;
				//spritemask2[i][j]=0;
		}
	}

/////////// INIZIALIZZAZIONE MATRICE DELLA FINESTRELLA /////
	for(i=0;i<WIMGY;i++){
		for(j=0;j<WIMGX;j++){
			miniwmask[i][j]=0;
		}
	}

////// INIZIALIZZAZIONE MATRICE DELLE LISTE DELLE TILE/////////////

	x=0;					// x ä azzerato solo una volta cosç le
							// 2 tilebar sono consecutive
	for(k=0;k<2;k++){
		for(i=0;i<2;i++){
			for(j=0;j<NBARTEXT;j++){
				spritemask[k][i][j]=x++;
				//spritemask2[i][j]=0;
			}
		}
	}
	currenttile[0]=7;
	currenttile[1]=7;

///////////////// BUFFER PER IL DOUBLE BUFFERING //////////////

	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	sfondo=create_bitmap(SCREEN_W,SCREEN_H);
	//show_mouse(buffer);
	//textures=mappa.RetTextBmp(0);
	mappa.RetTextBmp(0,textures);

	clear_to_color(buffer,DESK_COL);
	clear(sfondo);
	//clear_to_color(lvldis,BACKG_COL);

//////////////////////////////////////////////////////////////////

for(i=0,y=0,k=0;i<16;i++,y+=UNITY){
		for(j=0,x=0;j<16;j++,x+=UNITX,k++){
			blit(sprites[k],buffer,0,0,x,y,UNITX,UNITY);
		}
	}
	readkey();

/////////////////////////// PUTTAGGIO  ///////////////////////////

	DrawMainWindow();
	DrawMiniWindow();
	DrawTerranBar();
	DrawTileLists();

	//show_mouse(buffer);

	blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	//rectfill(screen,0,0,100,100,5);

//////////////////////////////////////////////////////////////////

////////////////// INPUT E CONTROLLI  ////////////////////////////

	set_palette(color);


	while(!key[KEY_ESC]){

		if(key[KEY_RSHIFT]||key[KEY_LSHIFT]){
			speed=true;
		}else{
			speed=false;
		}
		if(key[KEY_PLUS_PAD]){
			cursize=2;
			moved=true;
		}
		if(key[KEY_MINUS_PAD]){
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
			//relx=cursorx*MUNITX;

			moved=true;
		}
		if(key[KEY_RIGHT]&&cursorx<NSPRITEX-cursize&&!pushed){
			if(!speed)
				pushed=true;

			cursorx++;
			if(cursize==2&&cursorx<NSPRITEX-cursize)
				cursorx++;
			//relx=cursorx*MUNITX;

			moved=true;
		}
		if(key[KEY_UP]&&cursory&&!pushed){
			if(!speed)
				pushed=true;

			cursory--;
			if(cursize==2&&cursory)
				cursory--;
			//rely=cursory*MUNITY;

			moved=true;
		}
		if(key[KEY_DOWN]&&cursory<NSPRITEY-cursize&&!pushed){
			if(!speed)
				pushed=true;

			cursory++;
			if(cursize==2&&cursory<NSPRITEY-cursize)
				cursory++;
			//rely=cursory*MUNITY;

			moved=true;
		}

		/*if(key[KEY_PLUS_PAD]&&!pushed){
			pushed=true;
			BACKG_COL++;
			moved=true;
		}  */

		if(key[KEY_Z]&&!pushed){
			if(!speed)
				pushed=true;

			MoveTileBar(DIR_LEFT,0);
			//spritecont--;
			//spritecont2--;
			//relx=cursorx*MUNITX;

			moved=true;
		}
		if(key[KEY_X]&&!pushed){
			if(!speed)
				pushed=true;

			MoveTileBar(DIR_RIGHT,0);
			//spritecont++;
			//spritecont2++;
			//relx=cursorx*MUNITX;

			moved=true;
		}

		/*if(key[KEY_A]&&!pushed){
			if(!speed)
				pushed=true;

			if(terrancont>0)
				terrancont--;
			else
				terrancont=MAX_TERR;

			moved=true;
		}
		if(key[KEY_S]&&!pushed){
			if(!speed)
				pushed=true;

			terrancont++;
			if(terrancont>MAX_TERR)
				terrancont=0;

			moved=true;
		}

		if(key[KEY_Q]&&!pushed){
			if(!speed)
				pushed=true;

			if(solidcont>0)
				solidcont--;
			else
				solidcont=MAX_SOLID;

			moved=true;
		}
		if(key[KEY_W]&&!pushed){
			if(!speed)
				pushed=true;

			solidcont++;
			if(solidcont>MAX_SOLID)
				solidcont=0;

			moved=true;
		}*/
		/*
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
		*/


		if(key[KEY_ENTER]){
			clear_to_color(buffer,0);

			//for(i=0;i<NSPRITEY;i++){
			//	for(j=0;j<NSPRITEX;j++){
			//		livello.SetSprite(i*NSPRITEX+j,mainwind[i][j]);
			//	}
			//}
			//mappa.InsertNLevel(currentlevel,livello);
			//mappa.OutLevel(0,0,0,0,0,0);

			for(i=0,y=0;i<NSPRITEY;i++,y+=UNITY){
				for(j=0,x=0;j<NSPRITEX;j++,x+=UNITX){
					blit(sprites[mainwind[i][j]],buffer,0,0,
							x,y,UNITX,UNITY);
				}
			}

			vsync();
			blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

			while(!key[KEY_BACKSPACE]);
			moved=true;
		}

		if(mouse_b&&!pushed){

			if(!speed)
				pushed=true;

			MWind=MouseDetectClick();

			switch(MWind){

				case 1:
					break;

				case 2:
					cursorx=(mouse_x-MAINWINDX)/MUNITX;
					cursory=(mouse_y-MAINWINDY)/MUNITY;

					if((cursorx%cursize))
						cursorx-=1;
					if((cursory%cursize))
						cursory-=1;

					if(mouse_b&1)
						selectbar=0;
					else
						selectbar=1;

					//moved=true;
					print=true;

					break;

				case 3:
					break;

				case 4:
					break;

				case 5:
					break;

				case 6:
					break;

				case 7:
					if(mouse_b&1)
						MoveTileBar(DIR_LEFT,0);
					else
						MoveTileBar(DIR_RIGHT,0);
					break;

				case 8:
					if(mouse_b&1)
						MoveTileBar(DIR_LEFT,1);
					else
						MoveTileBar(DIR_RIGHT,1);
					break;

				default:
					break;
			}

			moved=true;
		}

		if(print||toggleprint){

			print=false;

			PrintBlock();

		}

		if(moved){
			clear_to_color(buffer,DESK_COL);


			DrawMainWindow();

			DrawMiniWindow();


				// Se ä premuto 'toggleprint' ( che ä un Pokemon? )
			if(toggleprint){
				rectfill(buffer,300,110,320,130,CURS_COL);
			}else{
				rectfill(buffer,300,110,320,130,DESK_COL);
			}
			/*
			textprintf(buffer,font,250,60,255,"Sol : %d",solidcont);
			textprintf(buffer,font,250,70,255,"Terr: %d",terrancont);

			*/

			DrawTerranBar();
			DrawTileLists();

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
			if(mouse_b)
				pushed=true;
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
	for(i=0;i<4;i++){
		destroy_bitmap(solidimg[i]);
	}

	for(i=0;i<10;i++){
		destroy_bitmap(terrainimg[i]);
	}

	destroy_bitmap(textures);
	destroy_bitmap(sldbmp);
	destroy_bitmap(terbmp);
	//destroy_bitmap(lvldis);
	destroy_bitmap(buffer);
	destroy_bitmap(sfondo);

	readkey();
	GameExit();

	fclose(filelog);
	printf("Programmed with DJGPP RHIDE Allegro");

	//puts(errmess);

	getch();


	return 0;

}
