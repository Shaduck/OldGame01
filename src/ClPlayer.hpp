
#ifndef CLPLAYER_HPP
#define CLPLAYER_HPP

#include<allegro.h>
#include<default.h>

#include"D:\djgpp\game01\ClChar.cpp"
#include"D:\djgpp\game01\ClObject.hpp"

class player : public character{

			int life,lifemax;

			weapon arma;

			int noggetti;
			object *oggetti;


	};

#include"D:\djgpp\game01\ClPlayer.cpp"
//#include"D:\djgpp\game01\ClMove.cpp"

#endif
