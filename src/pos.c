#include "../include/pos.h"

Pos* InitPos(int y, int x, int z){
	struct Pos* init_pos;
	init_pos = malloc(sizeof(Pos));
	init_pos->y = y;
	init_pos->x = x;
	init_pos->z = z;
	return init_pos;
}

void SetPos(Pos* pos, int y, int x, int z){
	if( pos != NULL ){
		pos->y = y;
		pos->x = z;
		pos->z = z;
	}
}

void FreePos(Pos* pos_to_free){
	if( pos_to_free != NULL ){
		free(pos_to_free);
		pos_to_free = NULL;
	}
}
