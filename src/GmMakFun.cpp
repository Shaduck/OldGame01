
void GameInit(void)
{

	allegro_init();
   	install_keyboard();
   	install_timer();
	install_mouse();
	clear_keybuf();

	set_mouse_speed(1,1);

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


//////////// Disegno dello schermo principale /////////////////////

void DrawMainWindow(void)
{
	int i,j,k,x,y;
	int relx;
	int rely;

	rectfill(buffer,MAINWINDX,MAINWINDY,MAINWINDLARGH,
									MAINWINDALT,BACKG_COL);

	for(i=0,y=MAINWINDY,k=0;i<NSPRITEY;i++,y+=MUNITY){
		for(j=0,x=MAINWINDX;j<NSPRITEX;j++,x+=MUNITX,k++){
			stretch_blit(sprites[mainwind[i][j]],
						buffer,0,0,UNITX,UNITY,x,y,MUNITX,MUNITY);
		}
	}

	relx=(cursorx*MUNITX)+MAINWINDX;
	rely=(cursory*MUNITY)+MAINWINDY;

	if(cursize==1)
		rect(buffer,relx,rely,relx+MUNITX-1,rely+MUNITY-1,CURS_COL);
	else
		rect(buffer,relx,rely,relx+(2*MUNITX)-1,
					rely+(2*MUNITY)-1,CURS_COL);
	

	return;
}

//////////////// Disegno della finestra laterale //////////////////

void DrawMiniWindow(void)
{
	int i,j,x,y;
	//int startx=0;
	//int starty=0;
	int tmpx=0;
	int tmpy=0;

	//startx=cursorx-2;
	//if(startx<0)
	//	startx=0-startx;
	//starty=cursory-2;
	//if(starty<0)
	//	starty=0-starty;

	for(i=0;i<WIMGY;i++){
		for(j=0;j<WIMGX;j++){
			tmpy=cursory+i-2;
			tmpx=cursorx+j-2;
			if(tmpy>=0&&(tmpy<MAINWINDALT-3)&&
				tmpx>=0&&(tmpx<MAINWINDLARGH-3)){
				miniwmask[i][j]=mainwind[tmpy][tmpx];
			}else{
				miniwmask[i][j]=0;
			}
		}
	}

	for(i=0,y=MINIWINDY;i<WIMGY;i++,y+=UNITY){
		for(j=0,x=MINIWINDX;j<WIMGX;j++,x+=UNITX){
			blit(sprites[miniwmask[i][j]],buffer,0,0,x,y,UNITX,UNITY);
		}
	}
	return;
}

/////////////// Disegno elenco sprite ///////////////////

void DrawTileLists(void)
{
	int i,j,x,y;
	int bar1x,bar1y;
	int off1x,off1y;
	int bar2x,bar2y;
	//int off2x,off2y;

	byte k=0;
	for(i=0,y=TEXTBAR1Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR1X+UNITX;j<NBARTEXT;j++,x+=UNITX){
			blit(sprites[spritemask[k][i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

/////////////// Disegno elenco sprite numero 2 ///////////////////

	k=1;
	for(i=0,y=TEXTBAR2Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR2X+UNITX;j<NBARTEXT;j++,x+=UNITX){
			blit(sprites[spritemask[k][i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

	bar1x=TEXTBAR1X+((currenttile[0]+1)*UNITX);
	bar1y=TEXTBAR1Y;

	bar2x=TEXTBAR2X+((currenttile[1]+1)*UNITX);
	bar2y=TEXTBAR2Y;

	off1x=UNITX*cursize;
	off1y=UNITY*cursize;

	rect(buffer,bar1x,bar1y,bar1x+off1x,bar1y+off1y,CURS_COL);
	rect(buffer,bar2x,bar2y,bar2x+off1x,bar2y+off1y,CURS_COL);

	textprintf(buffer,font,250,120,3,"%d",
								spritemask[0][0][currenttile[0]]);

	return;
}


void MoveTileBar(int direction,int barnum)
{
	int i,j;

	switch(direction){

		case DIR_RIGHT:

			/*
			for(int i=1;i<NBARTEXT-1;i++)
				spritemask[barnum][0][i-1]=spritemask[barnum][0][i];

			spritemask[barnum][0][NBARTEXT-1]=
										spritemask[barnum][1][0];

			for(int i=1;i<NBARTEXT-1;i++)
				spritemask[barnum][1][i-1]=spritemask[barnum][1][i];
			*/

			for(i=0;i<2;i++){
				for(j=0;j<NBARTEXT;j++){
					if(spritemask[barnum][i][j]==255){
						spritemask[barnum][i][j]=0;
					}else{
						spritemask[barnum][i][j]++;
					}
				}
			}

			break;

		case DIR_LEFT:

			/*
			for(int i=NBARTEXT-1;i>0;i--)
				spritemask[barnum][1][i]=spritemask[barnum][1][i-1];

			spritemask[barnum][1][0]=
								spritemask[barnum][0][NBARTEXT-1];

			for(int i=NBARTEXT-1;i>0;i--){
				spritemask[barnum][0][i]=spritemask[barnum][0][i-1];
			}
			*/

			for(i=0;i<2;i++){
				for(j=0;j<NBARTEXT;j++){
					if(spritemask[barnum][i][j]==0){
						spritemask[barnum][i][j]=255;
					}else{
						spritemask[barnum][i][j]--;
					}
				}
			}

			break;

			//fprintf(filelog,"%d \n",spritemask[barnum][0][0]);

	}
	/*
	byte spritemask1[2][18];
	int currenttile1;

	byte spritemask2[2][18];
	int currenttile2;
	  */
	return;
}

void DrawTerranBar(void)
{
	int j,x;
	int bar1x,bar1y;
	//int off1x,off1y;
	int bar2x,bar2y;
	//int off2x,off2y;

	//byte k=0;
	//for(i=0,y=TERRBAR1Y;i<2;i++,y+=UNITY){
		for(j=0,x=TERRBAR1X+UNITX;j<NBARTERR;j++,x+=UNITX){
			blit(terrainimg[terranmask[j]],buffer,0,0,x,TERRBAR1Y,
											UNITX,UNITY);
		}
	//}

/////////////// Disegno elenco sprite numero 2 ///////////////////

	//k=1;
	//for(i=0,y=TERRBAR2Y;i<2;i++,y+=UNITY){
		for(j=0,x=TERRBAR2X+UNITX;j<NBARTERR;j++,x+=UNITX){
			blit(terrainimg[terranmask[j]],buffer,0,0,x,TERRBAR2Y,
											UNITX,UNITY);
		}
	//}

	bar1x=TERRBAR1X+((currentterran[0]+1)*UNITX);
	bar1y=TERRBAR1Y;

	bar2x=TERRBAR2X+((currentterran[1]+1)*UNITX);
	bar2y=TEXTBAR2Y;

	//off1x=UNITX*cursize;
	//off1y=UNITY*cursize;

	rect(buffer,bar1x,bar1y,bar1x+UNITX,bar1y+UNITY,CURS_COL);
	rect(buffer,bar2x,bar2y,bar2x+UNITX,bar2y+UNITY,CURS_COL);


	return;
}

void DrawSolidBar(void)
{
	int i,j,x,y;
	int bar1x,bar1y;
	int off1x,off1y;
	int bar2x,bar2y;
	//int off2x,off2y;

	byte k=0;
	for(i=0,y=TEXTBAR1Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR1X+UNITX;j<NBARTEXT;j++,x+=UNITX){
			blit(sprites[spritemask[k][i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

/////////////// Disegno elenco sprite numero 2 ///////////////////

	k=1;
	for(i=0,y=TEXTBAR2Y;i<2;i++,y+=UNITY){
		for(j=0,x=TEXTBAR2X+UNITX;j<NBARTEXT;j++,x+=UNITX){
			blit(sprites[spritemask[k][i][j]],buffer,0,0,x,y,
											UNITX,UNITY);
		}
	}

	bar1x=TEXTBAR1X+((currenttile[0]+1)*UNITX);
	bar1y=TEXTBAR1Y;

	bar2x=TEXTBAR2X+((currenttile[1]+1)*UNITX);
	bar2y=TEXTBAR2Y;

	off1x=UNITX*cursize;
	off1y=UNITY*cursize;

	rect(buffer,bar1x,bar1y,bar1x+off1x,bar1y+off1y,CURS_COL);
	rect(buffer,bar2x,bar2y,bar2x+off1x,bar2y+off1y,CURS_COL);


	return;
}

void PrintBlock(void)
{
	int i,j;
	for(i=0;i<cursize;i++){
		for(j=0;j<cursize;j++){
			mainwind[cursory+i][cursorx+j]=
				spritemask[selectbar][i][currenttile[0]+j];
		}
	}

	return;
}

int MouseDetectClick(void)
{
	int i;
	//mouse

	for(i=0;i<NMOUSEPOINT;i++){
		if(mouse_x>MouseP[i][0]&&mouse_y>MouseP[i][1]&&
				mouse_x<MouseP[i][2]&&mouse_y<MouseP[i][3]){
			return i+1;
		}
	}
	return 0;
}

void InitMPoints(void)
{
	MouseP[0][0]=MAPCOUNTBARX;
	MouseP[0][1]=MAPCOUNTBARY;
	MouseP[0][2]=MAPCOUNTBARX+MAPCOUNTLARGH;
	MouseP[0][3]=MAPCOUNTBARY+MAPCOUNTALT;

	MouseP[1][0]=MAINWINDX;
	MouseP[1][1]=MAINWINDY;
	MouseP[1][2]=MAINWINDX+MAINWINDLARGH;
	MouseP[1][3]=MAINWINDY+MAINWINDALT;

	MouseP[2][0]=0;
	MouseP[2][1]=0;
	MouseP[2][2]=0;
	MouseP[2][3]=0;

	MouseP[3][0]=0;
	MouseP[3][1]=0;
	MouseP[3][2]=0;
	MouseP[3][3]=0;

	MouseP[4][0]=0;
	MouseP[4][1]=0;
	MouseP[4][2]=0;
	MouseP[4][3]=0;

	MouseP[5][0]=0;
	MouseP[5][1]=0;
	MouseP[5][2]=0;
	MouseP[5][3]=0;

	MouseP[6][0]=TEXTBAR1X;
	MouseP[6][1]=TEXTBAR1Y;
	MouseP[6][2]=TEXTBAR1X+TEXTBARLARGH;
	MouseP[6][3]=TEXTBAR1Y+TEXTBARALT;

	MouseP[7][0]=TEXTBAR2X;
	MouseP[7][1]=TEXTBAR2Y;
	MouseP[7][2]=TEXTBAR2X+TEXTBARLARGH;
	MouseP[7][3]=TEXTBAR2Y+TEXTBARALT;
}


