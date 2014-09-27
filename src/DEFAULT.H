#ifndef DEFAULT_H

#define DEFAULT_H


#include<math.h>

const double M_PI = 3.14159265359;

#define ERROR 0;
#define OK 1;


//const int MAXX=320;
//const int MAXY=200;

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

float *Cos;
float *Sen;

word *offset;

void InitOffset(int,int);
void DelOffset(void);
void InitCos(int);
void DelCos(void);
void InitSen(int);
void DelSen(void);

inline int settra(int,int,int);


void InitOffset(int step,int rout)
{
	offset=new word[rout];
	offset[0]=0;
	for(byte i=1;i<rout;i++)offset[i]=offset[i-1]+step;
	return;
}

void DelOffset(void)
{
	delete [] offset;
	return;
}

void InitCos(int anglemax)
{
	Cos=new float [anglemax];
	for(int i=0;i<anglemax;i++)
		Cos[i]=cos(M_PI*i/180);
	return;
}

void DelCos(void)
{
	delete [] Cos;
	return;
}

void InitSen(int anglemax)
{
	Sen=new float [anglemax];
	for(int i=0;i<anglemax;i++)
		Sen[i]=sin(M_PI*i/180);
	return;
}

void DelSen(void)
{
	delete [] Sen;
	return;
}



inline int settra(int num,int min,int max)
{
	return (num<min)?min:(num>max)?max:num;
	/*if(num<min){
		return min;
	}else{
		if(num>max){
			return max;
		}else{
			return num;
		}
	} */
}

#endif