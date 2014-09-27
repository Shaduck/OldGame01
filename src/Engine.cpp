
bool button[128];	//	flag che servono per evitare la ripetizione
						//	automatica dei tasti;

/************************************************************************
*							Programma  Principale  						*
************************************************************************/

void engine(void)
{

	//bool setsprite=0;
////////////////////////  Dichiarazione Variabili ///////////////////////

	//int i,j;
	//byte x,y;

	byte temp=0;
	bool changelvl=false;
	bool exitflag=false;
	byte nscreen=0;

	//FILE *fp;

/////////////////////////////////////////////////////////////////////////

////////////////////// Classi  Custom  //////////////////////////////////

	T_Character player;

	T_Map mappa;

	//T_Texture pattern;

	//mappa.InitLevel();
	//pattern.InitTexture();

/////////////////////////////////////////////////////////////////////////

////////////////////// Programma  Principale  ///////////////////////////

		// INIT MASK
	//while(!exitflag){

////////////////// Gestione Mappa ///////////////////////////////////

			// Caricamento file mappa
			// Questo verr… fatto usando la classe apposita :)

		//fp=fopen("D:\\DJGPP\\Project\\Mappa01.map","r");
		//fp=fopen("Mappa01.map","r");
		if(!mappa.SetMapFile("Indexmap.map", 1))
			return;

		//fclose(fp);
	//	if(!fp)
	//		return;

	//	for(i=0;i<MASKY;i++){
	//		for(j=0;j<MASKX;j++){
			//	fread(&mask[i][j],sizeof(level),1,fp);
	//		}
	//	}

		// Caricamento del file con le texture del terreno!!

		//textures=create_bitmap(XTEXTFILE,YTEXTFILE);
		//textarch[0]=create_bitmap(XTEXTFILE,YTEXTFILE);
		//textarch[1]=create_bitmap(XTEXTFILE,YTEXTFILE);

	  /*
		//textures=load_bmp("D:\\DJGPP\\Game01\\Moveto.bmp",color);
		textures=load_bmp("Moveto.bmp",color);
		if(!textures){
			strcpy(errmess,"Impossibile caricare texture");
			return;
		}

		pattern.LoadTexture(textures);
		*/
		if(!mappa.SetTextureFile("txtindex.txt",1)) // File indice
												// delle texture
			return;

		/*textarch[1]=load_bmp("Moveto2.bmp",colorarch[1]);
		if(!textarch[1])
			return;*/

		//set_palette(color);

		//mappa.SetMaskTerr(terreno);
		//mappa.SetMaskSolid(solid);
		//mappa.SetMaskSfondo(sfondo);

		//mappa.SetTexture(0);
		//mappa.SetLevel(0);

/////////////////////////////////////////////////////////////////////

		player.InitCharacter(PLAYER_LARGH,PLAYER_ALT);
		rectfill(player.image,0,0,PLAYER_LARGH*UNITX-1,
											PLAYER_ALT*UNITY-1,255);
		player.setposition(30,30);


			// INIT MASK
	while(!exitflag){

		/*if(!setsprite){
			blit(textarch[0],textures,0,0,0,0,XTEXTFILE,YTEXTFILE);
			set_palette(colorarch[0]);
		}else{
			blit(textarch[1],textures,0,0,0,0,XTEXTFILE,YTEXTFILE);
			set_palette(colorarch[1]);
		}  */



		changelvl=false;


   		while (!exitflag&&!changelvl) {

//////////////////// MOVIMENTO  DEL  PERSONAGGIO  ///////////////////

			if(key[KEY_ESC])
				exitflag=true;

		/*	if(key[KEY_C]){
				if(!setsprite){
					setsprite=1;
					changelvl=true;
				}else{
					setsprite=0;
					changelvl=true;
				}
			}*/

			if(key[KEY_UP]){
				if(!player.setclimb(DIR_UP)){
					player.setstairs(DIR_UP);
				}

			}

			if(key[KEY_DOWN]){
				if(!player.setclimb(DIR_DOWN)){
					if(!player.setstairs(DIR_DOWN)){
						if(!button[KEY_DOWN]){
							button[KEY_DOWN]=true;
							player.setcrouch();
						}
					}
				}
			}


			if(key[KEY_LEFT]){
				player.setmove(DIR_LEFT);
			}

			if(key[KEY_RIGHT]){
				player.setmove(DIR_RIGHT);
			}

			if(key[KEY_SPACE]){
				if(!player.resgraspcl()){
					if(!player.resgraspst()){
						if(!button[KEY_SPACE]){
							button[KEY_SPACE]=true;
							player.setjump();
						}
					}
				}
			}


			temp=player.moveplatform();

			if(temp){
				//if(temp==DIR_UP){
				if(temp==DIR_LEFT){
					player.setcoordx(SCREEN_W-(UNITX*PLAYER_LARGH));
					if(nscreen>0)
						nscreen--;
					else
						exitflag=true;
					break;
				}

				if(temp==DIR_RIGHT){
					player.setcoordx(1);
					nscreen++;
					break;
				}

			}


	//	SE NON SI PREMONO I TASTI ...

			if(!key[KEY_RIGHT]){
				player.resmove();
			}

			if(!key[KEY_LEFT]){
				player.resmove();
			}

			if(!key[KEY_UP]){
				if(!player.resclimb()){
					player.resstairs();
				}
			}

			if(!key[KEY_DOWN]){
				if(!player.resclimb()){
					if(!player.resstairs()){
						if(button[KEY_DOWN]){
							button[KEY_DOWN]=false;
							player.rescrouch();
						}
					}
				}
			}

			if(!key[KEY_SPACE]&&button[KEY_SPACE]){
				button[KEY_SPACE]=false;
			}


///////////////////// FINE  MOVIMENTO  DEL  PERSONAGGIO ///////////////


			//blit(sfondo,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
			mappa.OutLevel(1,0,0,0,0,1);

	//   PUTTAGGIO  IMMAGINE  AL  POSTO  GIUSTO

			player.outimage(buffer);

			vsync();

   		 	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

   		}
	}

/////////////////////////////////////////////////////////////////////////

	//fclose(fp);

	//destroy_bitmap(textures);
	//destroy_bitmap(textarch[0]);
	//destroy_bitmap(textarch[1]);

}
