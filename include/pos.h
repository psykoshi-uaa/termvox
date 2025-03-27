#ifndef POS_H
#define POS_H
#include<stdlib.h>

struct Pos {
	int y;
	int x;
	int z;
} typedef Pos;


Pos* InitPos(int y, int x, int z);
void SetPos(Pos* pos, int y, int x, int z);
void FreePos(Pos* pos_to_free);
#endif
