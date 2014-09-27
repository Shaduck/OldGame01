#include<allegro.h>


volatile int timer;
          
void ticker()
{
	timer++;
}
          
END_OF_FUNCTION(ticker);


/************************************************************************
*			Sottoprogramma di inizializzazione dell'ambiente			*
************************************************************************/

void GameInit(void)
{
	allegro_init();
   	install_keyboard();
   	install_timer();

   	set_gfx_mode(GFX_VGA, 320, 200, 0, 0);
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
	allegro_exit();

 	return;
}

/************************************************************************
*							Programma  Principale  						*
************************************************************************/

const LARGH=20;
const ALTEZZ=20;



void main(void)
{


////////////////////////  Dichiarazione Variabili ///////////////////////

	LOCK_VARIABLE(timer);
	LOCK_FUNCTION(ticker);


   	BITMAP *buffer,*sfondo;
   	BITMAP *memory_bitmap1;
   	BITMAP *memory_bitmap2;
   	int c,x,y,i,j,cont1,cont2;

   	int matx,maty,xrap,yrap;
   	bool move=true;
   	unsigned char jump=0,contjp=0,cad=1;
	unsigned char speedx=1,speedy=4;

   	struct coord{
   		unsigned char x;
		unsigned char y;
		};
   	coord mask[200][320];

	int rc=0;

   	bool mat[10][16]={
   		0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,
		0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,
		1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,1,0,0,1,1,0,0,0,0,1,0,0,1,1,
		1,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,
		1,0,1,0,0,0,1,0,0,0,0,1,1,0,0,1,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1
			};

/////////////////////////////////////////////////////////////////////////



/////////////////// Inizializzazione Programma //////////////////////////

	GameInit();

	timer=0;
	if(install_int_ex (ticker, MSEC_TO_TIMER(2) /*3000*/ ) ){
		GameExit();
		return 1;
	}
/////////////////////////////////////////////////////////////////////////



////////////////// Inizializzazione  Variabili  /////////////////////////

   	/* make a memory bitmap sized 20x20 */
   	memory_bitmap1 = create_bitmap(LARGH, ALTEZZ);
   	memory_bitmap2 = create_bitmap(LARGH, ALTEZZ);

   	/* draw some circles onto it */
   	clear(memory_bitmap1);
   	clear(memory_bitmap2);

    rectfill(memory_bitmap1, 0, 0, 19, 19, 8);
	rectfill(memory_bitmap2, 0, 0, 19, 19, 6);

   	/* allocate the memory buffer */
   	sfondo = create_bitmap(SCREEN_W, SCREEN_H);
   	buffer = create_bitmap(SCREEN_W, SCREEN_H);

	/* preparazione della maschera */
	cont1=0;
	cont2=0;
	i=0;
	j=0;
	for(y=0;y<200;y++){

	   	j=0;
	   	for(x=0;x<320;x++){
		  	mask[y][x].x=j;
		  	mask[y][x].y=i;

		  	cont1++;
		  	if(cont1>=20){
			  	cont1=0;
				j++;
			}
	   	}
    	cont2++;
		if(cont2>=20){
		  	cont2=0;
		  	i++;
		}
	}


   	/* blit lots of copies of it onto the screen */
   	for (y=0; y<10; y++)
		for (x=0; x<16; x++)
	 		if(mat[y][x])
			 	blit(memory_bitmap1, sfondo, 0, 0, x*20, y*20, 20, 20);
			else
				blit(memory_bitmap2, sfondo, 0, 0, x*20, y*20, 20, 20);
/////////////////////////////////////////////////////////////////////////



////////////////////// Programma  Principale  ///////////////////////////

   	x=10;
	y=10;

   	while (!key[KEY_ESC]) {
      	//clear(buffer);

		blit(sfondo,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

		if(y>180)
			break;
		/*if(x<1||x>300)
			break;*/

	//  Gestione caduta
		if(cad){
			if(!mat[(mask[y][x].y+1)][mask[y][x].x]&&
				!mat[(mask[y][x+19].y+1)][mask[y][x+19].x]){
	  			y++;
				move=false;
			}else{
				//if(jump){
					jump=0;
				//}else{
   		 			move=true;
				//}
				cad=1;
			}
		}
		/*if(key[KEY_UP]&&y>0)
			y--;
		if(key[KEY_DOWN]&&y<199)
		  	y++;*/

	// CORSA
		if(key[KEY_RSHIFT]){
			speedx=2;
		}else{
			speedx=1;
		}

	//  ANDARE  a  SINISTRA
		if((key[KEY_LEFT]&&move)||jump==1){
			if(x<1)
				break;
			if(!mat[mask[y][x-speedx].y][mask[y][x-speedx].x]&&
				!mat[mask[y+19][x-speedx].y][mask[y+19][x-speedx].x]){
		  		x-=speedx;
			}

		}

	//  ANDARE  a  DESTRA
		if((key[KEY_RIGHT]&&move)||jump==3){
			if(x>299)
				break;
			if(!mat[mask[y][x+19+speedx].y][mask[y][x+19+speedx].x]&&
				!mat[mask[y+19][x+19+speedx].y][mask[y+19][x+19+speedx].x]){
		  		x+=speedx;
			}

		}

	//  GESTIONE  SALTO

	//  INIZIALIZZAZIONE   SALTO
		if(key[KEY_SPACE]&&move&&jump==0){
			contjp=0;
			jump=2;
			if(key[KEY_LEFT])
				jump=1;
			if(key[KEY_RIGHT])
				jump=3;
			cad=0;
			move=false;
		}

	//	SALITA  VERSO  L'ALTO
		if(jump&&!cad){
			if(!speedy){
				//contjp=0;
				//jump=false;
				cad=1;
			}
			contjp++;
			if(contjp>=5){
				contjp=0;
				speedy--;
			}

			if(!mat[mask[y-1][x].y][mask[y-1][x].x]&&
				!mat[mask[y-1][x+19].y][mask[y-1][x+19].x]){
				y-=speedy;
			}else{
				cad=1;
			}
			if(y<1){
				y=0;
				//cad=1;
			}
		}

	//  CADUTA  DAL  SALTO
		if(cad){
			if(speedy<4)
				speedy++;
			/*if(jump==1)
				x--;
			if(jump==3)
				x++;*/
		}

	//   PUTTAGGIO  IMMAGINE  AL  POSTO  GIUSTO

    	rectfill(buffer,x,y,x+19,y+19, 255);

    	//textout(buffer, font, "Double buffered (mode 13h)", 0, 0, 255);
    	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		while(retrace_count==rc/*timer<10*/){

		}
		rc=retrace_count;

		timer=0;

   	}

   	destroy_bitmap(buffer);
   	destroy_bitmap(memory_bitmap1);
   	destroy_bitmap(memory_bitmap2);

/////////////////////////////////////////////////////////////////////////



////////////////////////   Distrutturi  /////////////////////////////////

	readkey();

   	GameExit();

/////////////////////////////////////////////////////////////////////////

   	return 0;
}

