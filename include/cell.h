#ifndef CELL_H
#define CELL_H
#include <stdlib.h>
#include "pos.h"
#include "defines.h"

struct Cell {
	int index;
	int col[4];
	char fill;
	Pos *pos;
	Pos *draw_origin;
	int distance;
	struct Cell* next;
} typedef Cell;

Cell* InitCell(int index, int y, int x, int z);
void SetCell(Cell* cell, int index);
void FreeCell(Cell* cell_to_free);
void FreeCellStack(Cell* bottom_cell);
void PushCellStack(Cell* bottom_cell, Cell* new_cell);
Cell* PopCell(Cell* cell_to_pop);
int CellOffset(int y, int x);
void UpdateCellDistance(Pos origin, Cell* cell);
void UpdateCellDrawOrigin(Cell* cell, Pos* main_origin, Pos* cam_origin, float rotation);

void PrintCell(Cell* cell, int y, int x, int col_index, int bold);
void PrintCellStack(Cell* cell, int col_index, int bold);
void PrintCellFromStack(Cell* bottom_cell, int col_index, int bold, int z);
#endif
