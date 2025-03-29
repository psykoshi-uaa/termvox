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
	Pos* cell_draw_origin = InitPos(y, x, z);
	init_cell->draw_origin = cell_draw_origin;
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
		cell->fill = '/';
		break;
	case GRASS_INDEX:
		cell->col[0] = G_V;
		cell->col[1] = G_G;
		cell->col[2] = G_G;
		cell->col[3] = V_G;
		cell->fill = '^';
		break;
	case WATER_INDEX:
		cell->col[0] = V_V;
		cell->col[1] = W_C;
		cell->col[2] = C_C;
		cell->col[3] = C_B;
		cell->fill = '~';
		break;
	default:
		break;
	}

}

void FreeCell(Cell* cell_to_free){
	if( cell_to_free != NULL ){
		FreePos(cell_to_free->pos);
		FreePos(cell_to_free->draw_origin);
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

void UpdateCellDistance(Pos draw_origin, Cell* cell){
	int y = draw_origin.y + MAX_CELLS_1D / 2;
	int x = draw_origin.x + MAX_CELLS_1D / 2;
	cell->distance = sqrt(pow(cell->pos->y - y, 2) + pow(cell->pos->x - x, 2));
}

void UpdateCellDrawOrigin(Cell* cell, Pos* main_draw_origin, Pos* cam_draw_origin, float rotation){
	cell->draw_origin->y = ((cell->pos->x - MAX_CELLS_1D / 2) * sin(rotation) + ((cell->pos->y - MAX_CELLS_1D / 2) * cos(rotation)));
	cell->draw_origin->x = ((cell->pos->x - MAX_CELLS_1D / 2) * cos(rotation) - ((cell->pos->y - MAX_CELLS_1D / 2) * sin(rotation)));
	cell->draw_origin->y += cam_draw_origin->y;
	cell->draw_origin->x += cam_draw_origin->x;
}


//.2
void PrintCell(Cell* cell, int y, int x, int col_index, int bold){
	int yy = y - cell->pos->z;
	if( bold )
		attron(A_BOLD);
	attron(COLOR_PAIR(cell->col[col_index]));
	mvaddch(yy, x, cell->fill);
	attroff(COLOR_PAIR(cell->col[col_index]));
	if( bold )
		attroff(A_BOLD);
}

void PrintCellStack(Cell* bottom_cell, int col_index, int bold){
	Cell* temp = bottom_cell;
	while( temp != NULL ){
		PrintCell(temp, bottom_cell->draw_origin->y, bottom_cell->draw_origin->x, col_index, bold);
		temp = temp->next;
	}
}

void PrintCellFromStack(Cell* bottom_cell, int col_index, int bold, int z){
	Cell* temp = bottom_cell;
	while( (temp != NULL) && (temp->pos->z != z) ){
		temp = temp->next;
	}
	if( temp != NULL )
		PrintCell(temp, bottom_cell->draw_origin->y, bottom_cell->draw_origin->x, col_index, bold);
}
