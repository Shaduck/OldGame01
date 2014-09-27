
T_Map::T_Map(void)
{
	Mappa=NULL;
	NLevel=0;
	//CurrentLev=0;

	Texture=NULL;
	NTexture=0;
	//CurrentText=0;

	//Palette=NULL;
	//NPalette=0;
	//CurrentPal=0;

}

T_Map::~T_Map(void)
{
	if(Mappa)
		delete [] Mappa;
	if(Texture)
		delete [] Texture;

	//if(Palette)
	//	delete [] Palette;
}

byte T_Map::SetTextureFile(char *filedat,int ntext)
{

	DATAFILE *tileset;

	tileset=load_datafile(filedat);

	if(!tileset)
		return 1;

	// File di configurazione esterno ;)): Numero di tileset
	// indicato da ntext!

	NTexture=ntext;
	if(NTexture==0)
		return 2;

	Texture=new T_Texture[NTexture];

	for(int i=0;i<NTexture;i++){
		Texture[i].InitTexture(128,128);
	}

	for(int i=0;i<NTexture;i++){
		Texture[i].LoadTexture((BITMAP *)tileset[i].dat);
	}

	return 0;
}

bool T_Map::SetMapFile(char *nome,int nlev)
{
 	FILE *fmap;

	fmap=fopen(nome,"r");

	if(!fmap)
		return false;

	NLevel=nlev;

	Mappa=new T_Level [NLevel];

	for(int i=0;i<NLevel;i++){
		Mappa[i].InitLevel();
	}

	for(int i=0;i<NLevel;i++){
		if(!Mappa[i].LoadLevel(fmap)){
			return false;
		}
	}

	return true;
}

byte T_Map::OutLevel(int level,int leftlev,int toplev,int rightlev,
											int bottomlev,int texture)
{
	//byte *MaskText;

	if(level>NLevel)
		return 0;
	/*
	if(leftlev>NLevel)
		leftlev=0;
	if(toplev>NLevel)
		toplev=0;
	if(rightlev>NLevel)
		rightlev=0;
	if(bottomlev>NLevel)
		bottomlev=0;
	*/

	//MaskText=new byte[SPRITETOT];

	Mappa[level].OutCenterLevel();
	Mappa[leftlev].OutBordLevel(DIR_LEFT);
	Mappa[toplev].OutBordLevel(DIR_UP);
	Mappa[rightlev].OutBordLevel(DIR_RIGHT);
	Mappa[bottomlev].OutBordLevel(DIR_DOWN);

	Texture[texture].OutTexture(sfondo);

	//if(MaskText)
	//delete [] MaskText;

	return 1;
}

//////////////////////////// MANUTENZIONE //////////////////////////////

bool T_Map::LoadMap(FILE *fp)
{

	fread(&NLevel,sizeof(int),1,fp);
	//fread(&currlev,sizeof(int),1,fp);

	Mappa=new T_Level[NLevel];

	for(int i=0;i<NLevel;i++){
		Mappa[i].LoadLevel(fp);
	}
	return true;
}

bool T_Map::SaveMap(FILE *fp)
{

	fwrite(&NLevel,sizeof(int),1,fp);
	//fwrite(&currlev,sizeof(int),1,fp);

	//Mappa=new T_Level[nlevel];

	for(int i=0;i<NLevel;i++){
		Mappa[i].SaveLevel(fp);
	}
	return 1;

}

int T_Map::RetNLevel(void)
{
	return NLevel;
}

void T_Map::SetNLevel(int nlev)
{
	NLevel=nlev;
	return;
}

bool T_Map::InsertNLevel(int numlev,T_Level &newlvl)
{
	if(numlev>NLevel)
		return false;

	return Mappa[numlev].InsertLevel(newlvl);

	//return true;
}

int T_Map::RetNText(void)
{
	return NTexture;
}

void T_Map::RetTextBmp(int ntext,BITMAP *temp)
{
	Texture[ntext].RetTotalBmp(temp);
	return;
}




