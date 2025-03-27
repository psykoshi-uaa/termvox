#include <curses.h>
#include <math.h>
#include "../include/cell.h"
#include "../include/pos.h"
#include "../include/defines.h"

Cell* InitCell(int index, int y, int x, int z){
	Cell* init_cell = malloc(sizeof(Cell));
	SetCell(init_cell, index);
	Pos* cell_pos = InitPos(y, x, z);
	init_cell->pos = cell_pos;
	init_cell->next = NULL;
	return init_cell;
}

void SetCell(Cell* cell, int index){
	cell->index = index;
	switch( index ){
	case VOID_INDEX:
		cell->col[0] = M_V;
		cell->col[1] = M_V;
		cell->col[2] = M_V;
		cell->col[3] = M_V;
		cell->fill = '?';
		break;
	case DIRT_INDEX:
		cell->col[0] = Y_V;
		cell->col[1] = Y_Y;
		cell->col[2] = Y_Y;
		cell->col[3] = V_Y;
		cell->fill = '.';
		break;
	case CLIFF_INDEX:
		cell->col[0] = V_V;
		cell->col[1] = V_W;
		cell->col[2] = V_W;
		cell->col[3] = W_V;
		cell->fill = '#';
		break;
	case GRASS_INDEX:
		cell->col[0] = G_V;
		cell->col[1] = G_G;
		cell->col[2] = G_G;
		cell->col[3] = V_G;
		cell->fill = '/';
		break;
	case WATER_INDEX:
		cell->col[0] = V_V;
		cell->col[1] = W_B;
		cell->col[2] = W_B;
		cell->col[3] = C_B;
		cell->fill = 'W';
		break;
	default:
		break;
	}

}

void FreeCell(Cell* cell_to_free){
	if( cell_to_free != NULL ){
		FreePos(cell_to_free->pos);
		free(cell_to_free);
		cell_to_free = NULL;
	}
}

void FreeCellStack(Cell* bottom_cell){
	Cell* temp = bottom_cell;
	while( temp != NULL ){
		temp = PopCell(bottom_cell);
	}
}

void PushCellStack(Cell* bottom_cell, Cell* new_cell){
	Cell* temp = bottom_cell;
	while( temp->next != NULL ){
		temp = temp->next;
	}
	temp->next = new_cell;
}

Cell* PopCell(Cell* cell_to_pop){
	Cell* temp = NULL;
	if( temp != NULL ){
		temp = cell_to_pop->next;
		FreeCell(cell_to_pop);
	}
	return temp;
}

int CellOffset(int y, int x){
	int offset = (y * MAX_CELLS_1D) + x;
	if( offset < MAX_CELLS_2D )
		return offset;
	return 0;
}

void UpdateCellDistance(Pos origin, Cell* cell){
	int y = origin.y + MAX_CELLS_1D / 2;
	int x = origin.x + MAX_CELLS_1D / 2;
	cell->distance = sqrt(pow(cell->pos->y - y, 2) + pow(cell->pos->x - x, 2));
}

//.2
void PrintCell(int y, int x, Cell* cell, int col_index, int bold){
	int yy = y - cell->pos->z;
	if( bold )
		attron(A_BOLD);
	attron(COLOR_PAIR(cell->col[col_index]));
	mvaddch(yy, x, cell->fill);
	attroff(COLOR_PAIR(cell->col[col_index]));
	if( bold )
		attroff(A_BOLD);
}

void PrintCellStack(Pos* origin1, Pos* origin2, float rotation, Cell* bottom_cell, int col_index, int bold){
	int origin_y = ((bottom_cell->pos->x - MAX_CELLS_1D / 2) * sin(rotation) + ((bottom_cell->pos->y - MAX_CELLS_1D / 2) * cos(rotation)));
	int origin_x = ((bottom_cell->pos->x - MAX_CELLS_1D / 2) * cos(rotation) - ((bottom_cell->pos->y - MAX_CELLS_1D / 2) * sin(rotation)));
	origin_y += origin2->y;
	origin_x += origin2->x;
	
	Cell* temp = bottom_cell;
	while( temp != NULL ){
		PrintCell(origin_y, origin_x, temp, col_index, bold);
		temp = temp->next;
	}
}

void PrintCellFromStack(Pos* origin1, Pos* origin2, float rotation, Cell* bottom_cell, int col_index, int bold, int z){
	int origin_y = ((bottom_cell->pos->x - MAX_CELLS_1D / 2) * sin(rotation) + ((bottom_cell->pos->y - MAX_CELLS_1D / 2) * cos(rotation)));
	int origin_x = ((bottom_cell->pos->x - MAX_CELLS_1D / 2) * cos(rotation) - ((bottom_cell->pos->y - MAX_CELLS_1D / 2) * sin(rotation)));
	origin_y += origin2->y;
	origin_x += origin2->x;
	
	Cell* temp = bottom_cell;
	while( (temp != NULL) && (temp->pos->z != z) ){
		temp = temp->next;
	}
	if( temp != NULL )
		PrintCell(origin_y, origin_x, temp, col_index, bold);
}
