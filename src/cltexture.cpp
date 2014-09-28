
#include "ClTexture.h"

#include "Costanti.h"
#include "Common.h"

T_Texture::T_Texture(void)
{
	texture=NULL;
	/*new (*BITMAP)[NTOTALTEXTURE];
	for(int i=0;i<NTOTALTEXT;i++)
		texture[i]=NULL;*/

	global=NULL;
}

T_Texture::~T_Texture(void)
{
	for(int i=0;i<NTOTALTEXT;i++)
		if(texture[i])
			destroy_bitmap(texture[i]);

	if(global)
		destroy_bitmap(global);

}

void T_Texture::InitTexture(int textx,int texty)
{
	byte x,y;
	int i;

	NXTEXTFILE=textx;
	NYTEXTFILE=texty;

	NTOTALTEXT=NXTEXTFILE*NYTEXTFILE;
	XTEXTFILE=NXTEXTFILE*UNITX;
	YTEXTFILE=NYTEXTFILE*UNITY;

	texture = new BITMAP *[NTOTALTEXT];

	for(int i=0;i<NTOTALTEXT;i++)
		texture[i]=NULL;

	global=create_bitmap(XTEXTFILE,YTEXTFILE);

	for(y=0,i=0;y<NYTEXTFILE;y++){
			for(x=0;x<NXTEXTFILE;x++,i++){
				texture[i]=create_sub_bitmap(global,x*UNITX,
											y*UNITY,UNITX,UNITY);
			}
		}

}

/*
byte T_Texture::SetIndexFile(char *nome)
{
	FILE *fp=NULL;

	fp=fopen(nome,"r");
	if(!fp)
		return 0;

	fread(&NumeroSet,sizeof(byte),1,fp);

	FileIndice=new IndexTexture[NumeroSet];
	for(int i=0;i<NumeroSet;i++)
		fread(&FileIndice[i],sizeof(IndexTexture),1,fp);

	fclose(fp);


	return 1;
}  */

byte T_Texture::LoadTexture(BITMAP *source)
{
	//RGB color[256];

	if(!source)
		return 0;

	blit(source,global,0,0,0,0,XTEXTFILE,YTEXTFILE);

	return 1;
}

/*
void T_Texture::LoadTexture(byte nset)
{
	RGB pal[256];
	if(!NumeroSet||nset>NumeroSet)
		return;

	global=load_bmp(FileIndice[nset].nomefile,pal);

	return;
}  */

/*
void T_Texture::OutTexture(BITMAP *out, int x, int y, byte code)
{
	blit(texture[code],out,0,0,x,y,UNITX,UNITY);
	return;
}
*/
void T_Texture::OutTexture(BITMAP *out)
{

	int limite_inf=NSPRITEY*UNITY;
	int limite_dx=NSPRITEX*UNITX;
	for (int y=0, i=0; y<limite_inf; y+=UNITY){
		for (int x=0; x<limite_dx; x+=UNITX, i++){
			blit(texture[MaskText[i]],out,0,0,x,y,UNITX,UNITY);
		}
	}

	return;
}

/////////////////////////////////////////////////////////////////////////

void T_Texture::RetTotalBmp(BITMAP *tmp)
{
	blit(global,tmp,0,0,0,0,128,128);

	return;
}

