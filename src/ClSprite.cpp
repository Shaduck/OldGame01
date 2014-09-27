
T_Texture::T_Texture(void)
{

	image=NULL;

}


T_Texture::~T_Texture(void)
{

	if(image)
		destroy_bitmap(image);

}

/////////////   INIZIALIZZAZIONE  ////////////////////////////////////////

void T_Texture::initsprite(byte nx,byte ny)
{

	return;

}

void T_Texture::outsprite(BITMAP *out,int x,int y)
{
	blit(image,out,0,0,x,y,largh,altezz);

}


bool T_Texture::loadsprite(BITMAP *point)
{
	image=point;

	return true;

}


