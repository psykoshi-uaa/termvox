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

void PrintCell(int y, int x, Cell* cell, int col_index, int bold);
void PrintCellStack(Pos* origin1, Pos* origin2, float rotation, Cell* cell, int col_index, int bold);
void PrintCellFromStack(Pos* origin1, Pos* origin2, float rotation, Cell* bottom_cell, int col_index, int bold, int z);
#endif
