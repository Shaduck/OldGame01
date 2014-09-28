
#ifndef DEFAULT_H
#define DEFAULT_H

#include<math.h>

const double M_PI = 3.14159265359;

const int ERROR = 0;
const int OK = 1;


//const int MAXX=320;
//const int MAXY=200;

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

extern float *Cos;
extern float *Sen;

extern word *offset;

void InitOffset(int,int);
void DelOffset(void);
void InitCos(int);
void DelCos(void);
void InitSen(int);
void DelSen(void);

inline int settra(int,int,int);

#endif