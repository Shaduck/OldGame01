
#include "cllevel.h"

#include "Costanti.h"
#include "Common.h"

T_Level::T_Level()
{
	map=NULL;
	sprite=NULL;

}

T_Level::~T_Level()
{
	if(map)
		delete [] map;

	if(sprite)
		delete [] sprite;
}

bool T_Level::InitLevel(void)
{
	map=new Levelst1[SPRITETOT];
	sprite=new byte[SPRITETOT];

	if(!map||!sprite)
		return false;

	for(int i=0;i<SPRITETOT;i++){
 		map[i].solid=0;
		map[i].terran=0;
		sprite[i]=0;
	}

	return true;
}

bool T_Level::LoadLevel(FILE *fp)
{

	fread(map,sizeof(Levelst1),SPRITETOT,fp);
	fread(sprite,sizeof(byte),SPRITETOT,fp);

	if(feof(fp))
		return false;

	return true;
}

byte T_Level::OutCenterLevel(void)
{
	int i;
	byte tmpsol=0;
	byte tmpterr=0;

	int limite_sup=(OVER_SPACE*UNITY);
	int limite_inf=((NSPRITEY+OVER_SPACE)*UNITY);
	int limite_sx=(LEFT_SPACE*UNITX);
	int limite_dx=((NSPRITEX+LEFT_SPACE)*UNITX);

	for(int y=limite_sup, i=0;y<limite_inf;y+=UNITY){
		for(int x=limite_sx;x<limite_dx;x+=UNITX, i++){
			tmpsol=map[i].solid;
			tmpterr=map[i].terran;
			for(byte k1=0;k1<UNITY;k1++){
				for(byte k2=0;k2<UNITX;k2++){
					terreno[y+k1][x+k2]=tmpterr;
					solid[y+k1][x+k2]=tmpsol;
				}
			}
		}
	}

	for(i=0;i<SPRITETOT;i++)
		MaskText[i]=sprite[i];


	return 1;
}

byte T_Level::OutBordLevel(byte dir)
{
	//int i;

	byte tmpsol;
	byte tmpterr;

	int limite_sup;
	int limite_inf;
	int limite_sx;
	int limite_dx;

	switch(dir){

		case DIR_LEFT:
			limite_sup=(OVER_SPACE*UNITY);
			limite_inf=((NSPRITEY+OVER_SPACE)*UNITY);
			limite_sx=0;
			limite_dx=(LEFT_SPACE*UNITX);
			break;

		case DIR_RIGHT:
			limite_sup=(OVER_SPACE*UNITY);
			limite_inf=((NSPRITEY+OVER_SPACE)*UNITY);
			limite_sx=((NSPRITEX+LEFT_SPACE)*UNITX);
			limite_dx=(MASKX*UNITX);
			break;

		case DIR_UP:
			limite_sup=0;
			limite_inf=(OVER_SPACE*UNITY);
			limite_sx=(LEFT_SPACE*UNITX);
			limite_dx=((NSPRITEX+LEFT_SPACE)*UNITX);
			break;

		case DIR_DOWN:
			limite_sup=((NSPRITEY+OVER_SPACE)*UNITY);
			limite_inf=(MASKY*UNITY);
			limite_sx=(LEFT_SPACE*UNITX);
			limite_dx=((NSPRITEX+LEFT_SPACE)*UNITX);
			break;

		default:
			return 0;
	}

	for(int y=limite_sup, i=0;y<limite_inf;y+=UNITY){
		for(int x=limite_sx;x<limite_dx;x+=UNITX, i++){
			tmpsol=map[i].solid;
			tmpterr=map[i].terran;
			for(byte k1=0;k1<UNITY;k1++){
				for(byte k2=0;k2<UNITX;k2++){
					terreno[y+k1][x+k2]=tmpterr;
					solid[y+k1][x+k2]=tmpsol;
					//MaskTerr[y*UNITY+k1][x*UNITX+k2]=
					//					Mappa[CurrentLev].RetTerran(i);
					//MaskSol[y*UNITY+k1][x*UNITX+k2]=
					//					Mappa[CurrentLev].RetSolid(i);
				}
			}
		}
	}

	/*limite_inf=NSPRITEY*UNITY;
	limite_dx=NSPRITEX*UNITX;
	for (int y=0, i=0; y<limite_inf; y+=UNITY){
		for (int x=0; x<limite_dx; x+=UNITX, i++){
			texture[CurrentText].OutTexture(MaskSfondo,x,y,
									Mappa[CurrentLev].RetSprite(i));
		}
	}  */

	return 1;
}


////////////////////////////// MANUTENZIONE //////////////////////////////

byte T_Level::RetSolid(int x)
{
	return map[x].solid;
}

byte T_Level::RetTerran(int x)
{
	return map[x].terran;
}

byte T_Level::RetSprite(int x)
{
	return sprite[x];
}



void T_Level::SetSolid(int x,byte val)
{
	map[x].solid=val;
}

void T_Level::SetTerran(int x,byte val)
{
	map[x].terran=val;
}

void T_Level::SetSprite(int x,byte val)
{
	sprite[x]=val;
}

bool T_Level::SaveLevel(FILE *fp)
{
	//fputs("Salvataggio riuscito\n",fp);

	fread(map,sizeof(Levelst1),SPRITETOT,fp);
	fread(sprite,sizeof(byte),SPRITETOT,fp);

	fwrite(map,sizeof(Levelst1),SPRITETOT,fp);
	fwrite(sprite,sizeof(byte),SPRITETOT,fp);
	//fwrite(next,sizeof(int),4,fp);

	//if(feof(fp))
	//	return 0;

	return true;
}

bool T_Level::InsertLevel(T_Level &Livello)
{

	//byte *sprite;
	//Levelst1 *map;

	/*if(!map)
		map=new Levelst1[SPRITETOT];
		//delete [] map;

	if(!sprite)
		sprite=new byte[SPRITETOT];
		//delete [] sprite;
	  */
	//map=new Levelst1[SPRITETOT];
	//sprite=new byte[SPRITETOT];

	if(!map||!sprite){
		//return false;
		InitLevel();
	}

	for(int i=0;i<SPRITETOT;i++){
 		map[i].solid=Livello.map[i].solid;
		map[i].terran=Livello.map[i].terran;
	//}

	//for(int i=0;i<SPRITETOT;i++){
		sprite[i]=Livello.sprite[i];
	}

	return true;
}

/*
byte T_Level::RetNextLev(byte dir)
		// dir : 0:Left, 1:Up, 2:Right, 3:Down
{
 	return next[dir];

}
*/
