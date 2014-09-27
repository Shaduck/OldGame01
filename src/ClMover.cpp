
T_ScreenObj::T_ScreenObj(void)
{

	image=NULL;

}

T_ScreenObj::~T_ScreenObj(void)
{

	if(leftcp)
		delete [] leftcp;

	if(topcp)
		delete [] topcp;

}

/////////////   INIZIALIZZAZIONE  ////////////////////////////////////////

void T_ScreenObj::initcharacter(byte x,byte y)
{
	coordx=20;
	coordy=Y_OFFSET;

	nunitx=x;
	nunity=y;

	chlargh=x*UNITX;
	chaltezz=y*UNITY;

	normaly=y;
	crouchy=y/2;

	nleftcp=nunity+1;
	ntopcp=nunitx+1;

	leftcp=new byte[nleftcp];
	topcp=new byte[ntopcp];

	leftcp[0]=0;
	topcp[0]=0;

	for(byte i=1;i<nleftcp;i++)
		leftcp[i]=(UNITY*i)-1;

	for(byte i=1;i<ntopcp;i++)
		topcp[i]=(UNITX*i)-1;

	return;
}

void T_ScreenObj::InitImage(BITMAP *newimage)
{

	image=newimage;

	return;

}

void T_ScreenObj::setposition(int x,int y)
{
	coordx=X_OFFSET+x;
	coordy=Y_OFFSET+y;
	return;
}

void T_ScreenObj::setcoordx(int x)
{
	coordx=X_OFFSET+x;
	return;
}

void T_ScreenObj::setcoordy(int y)
{
	coordy=Y_OFFSET+y;
	return;
}

bool T_ScreenObj::testall(byte terr)
{
	for(byte y=0;y<nleftcp;y++){
		for(byte x=0;x<ntopcp;x++){

			if(terreno[coordy-leftcp[y]-1][coordx+topcp[x]]==terr)
				return true;

		}
	}
	return false;
}

byte T_ScreenObj::testint(byte y,byte terr)	// linea y di test
{
	if(terreno[coordy-leftcp[y]-1][coordx+topcp[0]]==terr){
		if(terreno[coordy-leftcp[y]-1][coordx+topcp[ntopcp-1]]==terr){
			return DIR_CENTRE;
		}else{
			return DIR_LEFT;
		}
	}
	if(terreno[coordy-leftcp[y]-1][coordx+topcp[ntopcp-1]]==terr){
			return DIR_RIGHT;
		}

	return false;
}

byte T_ScreenObj::testbottom(byte terr)
{
	if(terreno[coordy-1][coordx+topcp[0]]==terr){
		if(terreno[coordy-1][coordx+topcp[ntopcp-1]]==terr){
			return DIR_CENTRE;
		}else{
			return DIR_LEFT;
		}
	}
	if(terreno[coordy-1][coordx+topcp[ntopcp-1]]==terr){
		return DIR_RIGHT;
	}

	return 0;
}

byte T_ScreenObj::testunder(byte terr,byte pos=0)
{
	pos++;
	if(terreno[coordy+pos-1][coordx+topcp[0]]==terr){
		if(terreno[coordy+pos-1][coordx+topcp[ntopcp-1]]==terr){
			return DIR_CENTRE;
		}else{
			return DIR_LEFT;
		}
	}
	if(terreno[coordy+pos-1][coordx+topcp[ntopcp-1]]==terr){
		return DIR_RIGHT;
	}

	return 0;
}

byte T_ScreenObj::testtop(byte terr)
{
	if(terreno[coordy-chaltezz][coordx+topcp[0]]==terr){
		if(terreno[coordy-chaltezz][coordx+topcp[ntopcp-1]]==terr){
			return DIR_CENTRE;
		}else{
			return DIR_LEFT;
		}
	}
	if(terreno[coordy-chaltezz][coordx+topcp[ntopcp-1]]==terr){
		return DIR_RIGHT;
	}
	return 0;
}

byte T_ScreenObj::testover(byte terr,byte pos=0)
{
	pos++;
	if(terreno[coordy-chaltezz-pos][coordx+topcp[0]]==terr){
		if(terreno[coordy-chaltezz-pos][coordx+topcp[ntopcp-1]]==terr){
			return DIR_CENTRE;
		}else{
			return DIR_LEFT;
		}
	}
	if(terreno[coordy-chaltezz-pos][coordx+topcp[ntopcp-1]]==terr){
		return DIR_RIGHT;
	}
	return 0;
}

byte T_ScreenObj::TestBorder(void)
{

	if(coordx<X_OFFSET)
		return DIR_LEFT;

	if(coordy<Y_OFFSET-10)
		return DIR_UP;

	if(coordx>SCREEN_W-chlargh+X_OFFSET)
		return DIR_RIGHT;

	if(coordy>SCREEN_H+Y_OFFSET-1)
		return DIR_DOWN;

	return 0;
}

void T_ScreenObj::gocrouch(void)
{

	nunity=crouchy;

	chaltezz=nunity*UNITY;

	nleftcp=nunity+1;

	return;
}

void T_ScreenObj::goraise(void)
{

	nunity=normaly;

	chaltezz=nunity*UNITY;

	nleftcp=nunity+1;

	return;
}

bool T_ScreenObj::godown(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<ntopcp;i++){
			if(solid[coordy][coordx+topcp[i]]>sollim)
				return false;
		}
		coordy++;
	}
	return true;
}


bool T_ScreenObj::goleft(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<nleftcp;i++){
			if(solid[coordy-leftcp[i]-1][coordx-1]>sollim)
				return false;
		}
		coordx--;
	}
	return true;
}


bool T_ScreenObj::goright(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<nleftcp;i++){
			if(solid[coordy-leftcp[i]-1][coordx+chlargh]>sollim)
				return false;
		}
		coordx++;
	}
	return true;
}


bool T_ScreenObj::goup(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<ntopcp;i++){
			if(solid[coordy-chaltezz-1][coordx+topcp[i]]>sollim)
				return false;
		}
		coordy--;
	}
	return true;
}

void T_ScreenObj::outimage(BITMAP *out)
{

		blit(image,out,0,0,coordx-X_OFFSET,coordy-chaltezz-Y_OFFSET,
												chlargh,chaltezz);


		//terreno[coordy][coordx+topcp[0]]==terr
		//if(graspst)
			//putpixel(out,coordx-X_OFFSET,coordy-1/*-chaltezz*/-Y_OFFSET,5);
			//putpixel(out,coordx-X_OFFSET,coordy-1-chaltezz-Y_OFFSET,5);
			//putpixel(out,coordx-X_OFFSET+chlargh,coordy-1-Y_OFFSET,5);


}


