
#ifndef CLSPRITE_HPP
#define CLSPRITE_HPP

#include<allegro.h>
#include<default.h>

	//  Alcune costanti devono essere esterne:
	//	-	UNTIX	= 	Larghezza dei blocchi unitari
	//	-	UNITY	=	Altezza dei blocchi unitari

class T_Texture{



		public:

			T_Texture(void);
			~T_Texture(void);


			void initsprite(byte nx,byte ny);

			void outsprite(BITMAP *out,int x,int y);


			bool loadsprite(BITMAP *point);

		};

#include"D:\djgpp\game01\ClSprite.cpp"

#endif
