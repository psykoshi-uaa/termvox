#include <math.h>
#include <curses.h>
#include <stdlib.h>
//#include "../include/numanip.h"
#include "../include/island.h"
#include "../include/pos.h"
#include "../include/input.h"
#include "../include/cell.h"
#include "../include/camera.h"

Island* InitIsland(Pos* origin){
	Island* init_island = malloc(sizeof(Island));

	init_island->time_of_day = 9.0f;
	init_island->time_inc = 0.1f;
	init_island->origin = origin;
	init_island->camera = InitCamera();
	SetCameraPos(init_island->camera, MAX_CELLS_1D, MAX_CELLS_1D, 30);
	init_island->camera_translate_key = InitMoveKeys('w', 's', 'a', 'd');
	init_island->camera_rotate_key = InitMoveKeys('k', 'i', 'j', 'l');

	for( int y=0; y<MAX_CELLS_1D; y++ ){
		for( int x=0; x<MAX_CELLS_1D; x++ ){
			Cell* new_cell = InitCell(VOID_INDEX, y, x, 0);
			init_island->bottom_cell[CellOffset(y, x)] = new_cell;
			UpdateCellDistance(*init_island->origin, init_island->bottom_cell[CellOffset(y, x)]);
		}
	}
	return init_island;
}

void FreeIsland(Island* island){
	if( island != NULL ){
		for( int y=0; y<MAX_CELLS_1D; y++) {
			for( int x=0; x<MAX_CELLS_1D; x++ ){ FreeCellStack(island->bottom_cell[CellOffset(y, x)]); }
		}

		FreePos(island->origin);
		FreeCamera(island->camera);
		FreeMoveKeys(island->camera_translate_key);
		FreeMoveKeys(island->camera_rotate_key);
		free(island);
		island = NULL;
	}
}

void IslandGenerateLand(Island* island){
//TO BE DELETED, FOR DEBUGGING ----- START
	for( int y=0; y<MAX_CELLS_1D; y++) {
		for( int x=0; x<MAX_CELLS_1D; x++ ){
			for( int z=0; z<8; z++ ){
				int cell_index = VOID_INDEX;
				if( z < 3 )
					cell_index = CLIFF_INDEX;
				else if( z < 6 )
					cell_index = DIRT_INDEX;
				else
					cell_index = GRASS_INDEX;
				Cell* new_cell = InitCell(cell_index, y, x, z);
				PushCellStack(island->bottom_cell[CellOffset(y, x)], new_cell);
				UpdateCellDistance(*island->origin, island->bottom_cell[CellOffset(y, x)]);
			}
		}
	}
	Cell* new_cell = NULL;
	int cell_index = CLIFF_INDEX;
	for( int i=0;i<8;i++ ){
		new_cell = InitCell(cell_index, 1, 1, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(1, 1)], new_cell);
		new_cell = InitCell(cell_index, 2, 2, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(5, 5)], new_cell);
		new_cell = InitCell(cell_index, 1, 2, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(1, 2)], new_cell);
		new_cell = InitCell(cell_index, 2, 1, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(2, 1)], new_cell);
	}
	cell_index = VOID_INDEX;
	new_cell = InitCell(cell_index, 1, 1, 17);
	PushCellStack(island->bottom_cell[CellOffset(1, 1)], new_cell);
	new_cell = InitCell(cell_index, 2, 2, 17);
	PushCellStack(island->bottom_cell[CellOffset(2, 2)], new_cell);
	new_cell = InitCell(cell_index, 1, 2, 17);
	PushCellStack(island->bottom_cell[CellOffset(1, 2)], new_cell);
	new_cell = InitCell(cell_index, 2, 1, 17);
	PushCellStack(island->bottom_cell[CellOffset(2, 1)], new_cell);
	cell_index = CLIFF_INDEX;
	for( int i=0;i<8;i++ ){
		new_cell = InitCell(cell_index, 4, 4, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(4, 4)], new_cell);
		new_cell = InitCell(cell_index, 5, 5, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(5, 5)], new_cell);
		new_cell = InitCell(cell_index, 4, 5, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(4, 5)], new_cell);
		new_cell = InitCell(cell_index, 5, 4, 9+i);
		PushCellStack(island->bottom_cell[CellOffset(5, 4)], new_cell);
	}
	cell_index = DIRT_INDEX;
	new_cell = InitCell(cell_index, 4, 4, 17);
	PushCellStack(island->bottom_cell[CellOffset(4, 4)], new_cell);
	new_cell = InitCell(cell_index, 5, 5, 17);
	PushCellStack(island->bottom_cell[CellOffset(5, 5)], new_cell);
	new_cell = InitCell(cell_index, 4, 5, 17);
	PushCellStack(island->bottom_cell[CellOffset(4, 5)], new_cell);
	new_cell = InitCell(cell_index, 5, 4, 17);
	PushCellStack(island->bottom_cell[CellOffset(5, 4)], new_cell);
//TO BE DELETED, FOR DEBUGGING ----- END
}

void IslandGenerateWater(Island* island){

}

void IslandUpdateTimeOfDay(Island* island){
	island->is_bright_out = 0;
	if( (island->time_of_day > 8.0) && (island->time_of_day < 14.0) )
		island->is_bright_out = 1;

	if( island->time_of_day + island->time_inc < 24.0 )
		island->time_of_day += island->time_inc;
	else
		island->time_of_day = 0;

	island->time_of_day_shade = floor(island->time_of_day / 6);
}

void IslandUpdateCamera(Island* island, char user_inp){
	if( (island->camera != NULL) && (island->camera_translate_key != NULL) && (island->camera_rotate_key != NULL) ){
		UpdateMoveKeys(island->camera_translate_key, user_inp);
		UpdateMoveKeys(island->camera_rotate_key, user_inp);

		TranslateCamera(island->camera, *island->camera_translate_key, *island->camera_rotate_key);
		RotateCamera(island->camera, *island->camera_rotate_key, 10);		//MAGIC NUMBER
	}
}

void IslandEngine(Island* island, char user_inp){
	float cam_rot_z = island->camera->rotation;
	IslandUpdateCamera(island, user_inp);
	for( int z=0; z<island->camera->origin->z; z++ ){
		for( int y=0; y<MAX_CELLS_1D; y++) {
			for( int x=0; x<MAX_CELLS_1D; x++ ){
				if( z == 0 ){
					UpdateCellDrawOrigin(
						island->bottom_cell[CellOffset(y, x)],
						island->origin,
						island->camera->origin,
						island->camera->rotation
					);
				}
				PrintCellFromStack(
					island->bottom_cell[CellOffset(y, x)],
					island->time_of_day_shade,
					island->is_bright_out,
					z
				);
			}
		}
	}
}

void PrintIslandDebug(Island* island){
	mvprintw(0, 54, "island debug menu:");
	mvprintw(1, 50, "camera origin: { %i, %i, %i }", island->camera->origin->y, island->camera->origin->x, island->camera->origin->z);
	mvprintw(2, 50, "camera z rot: %f", island->camera->rotation);
	mvprintw(3, 50, "time of day: %f", island->time_of_day);
}
