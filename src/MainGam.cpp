
#include<stdio.h>

#include<allegro.h>

#include"default.h"


volatile int timer=0;			// Temporizzazioni del game
volatile int second=0;			// Secondi;


void ticker()
{
	timer++;

	if(timer>999){
		timer=0;
		second++;
	}
}
          
END_OF_FUNCTION(ticker);


#include"Costanti.cpp"
#include"Common.hpp"

#include"ClChar.hpp"

#include"ClMap.hpp"
//#include"ClTextur.hpp"
//#include"ClLevel.hpp"

//RGB color[256];

char errmess[30];

#include"Engine.cpp"


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
*			Sottoprogramma di inizializzazione dell'ambiente			*
************************************************************************/

void GameInit(void)
{
	allegro_init();
   	install_keyboard();
   	install_timer();

   	if(set_gfx_mode(GFX_AUTODETECT,RESOLUTION_X,RESOLUTION_Y, 0, 0)<0){
   		GameExit();
		printf("Impossibile impostare la scheda grafica!");
   		exit(-1);
	}
   	set_palette(desktop_palette);

	return;
}


int main(void)
{


/////////////////////// Inizializzazione Programma //////////////////////////

	LOCK_VARIABLE(timer);
	LOCK_VARIABLE(second);
    LOCK_FUNCTION(ticker);
	timer=0;
	if(install_int_ex (ticker, MSEC_TO_TIMER(1)) ){
		return 1;
	}

	GameInit();

	strcpy(errmess,"");

/////////////////////////////////////////////////////////////////////////


////////////////// Inizializzazione  Variabili  /////////////////////////

	/*for(int i=0;i<256;i++)
		pattern.initsprite();*/

   	sfondo = create_bitmap(SCREEN_W, SCREEN_H);
   	buffer = create_bitmap(SCREEN_W, SCREEN_H);

	clear(sfondo);


/////////////////////////////////////////////////////////////////////////

////////////////////// QUESTI  RESTERANNO  ///////////////////////////


	for(int i=0;i<128;i++)
		button[i]=false;

//////////////////////////////////////////////////////////////////////


	engine();

	destroy_bitmap(buffer);


////////////////////////   Distrutturi  /////////////////////////////////

	clear_keybuf();

	readkey();

   	GameExit();

	puts(errmess);

	printf("Creato con DJGPP,Allegro,RHIDE\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\t\t\t\t\t by Shaduck");
/////////////////////////////////////////////////////////////////////////

   	return 0;
}
