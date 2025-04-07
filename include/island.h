#ifndef ISLAND_H
#define ISLAND_H
#include <math.h>
#include "pos.h"
#include "input.h"
#include "cell.h"
#include "defines.h"
#include "camera.h"

struct Island {
	float time_of_day, time_inc;
	int is_bright_out, time_of_day_shade;
	Pos origin;
	Camera camera;
	MoveKeys camera_translate_key;
	MoveKeys camera_rotate_key;
	Cell* bottom_cell[MAX_CELLS_2D];
} typedef Island;

Island InitIsland(Pos origin);
void FreeIsland(Island* island);
void IslandGenerateLand(Island* island);
void IslandGenerateLayer(Island* island, int cell_index, Pos origin, Pos size);
void IslandGenerateHill(Island* island, int cell_index, Pos hill_origin, int base_radius, int height);
void IslandGenerateWater(Island* island);
void IslandUpdateTimeOfDay(Island* island);
void IslandUpdateCellDistance(Cell* cell);
void IslandEngine(Island* island, char user_inp);

void PrintIslandDebug(Island island);
#endif
