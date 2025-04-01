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
	Pos layer_origin = {12, 12, 1};
	Pos layer_size = {30, 30, 1};
	int new_height = layer_origin.z + 2;
	for( layer_origin.z; layer_origin.z<new_height; layer_origin.z++ ){
		IslandGenerateLayer(island, CLIFF_INDEX, layer_origin, layer_size);
	}
	new_height = layer_origin.z + 2;
	for( layer_origin.z; layer_origin.z<new_height; layer_origin.z++ ){
		IslandGenerateLayer(island, DIRT_INDEX, layer_origin, layer_size);
	}

	IslandGenerateHill(island, GRASS_INDEX, layer_origin, 5, 20);
//TO BE DELETED, FOR DEBUGGING ----- END
}

void IslandGenerateLayer(Island* island, int cell_index, Pos origin, Pos size){
	for( int y=0; y<size.y; y++){
		for( int x=0; x<size.x; x++){
			int new_y = y + origin.y - size.y/2;
			int new_x = x + origin.x - size.x/2;
			int new_z = origin.z;
			Cell* new_cell = InitCell(cell_index, new_y, new_x, new_z);
			if( (new_y >= 0) && (new_y < MAX_CELLS_1D)
			&& (new_x >= 0) && (new_x < MAX_CELLS_1D) ){
				PushCellStack(island->bottom_cell[CellOffset(new_y, new_x)], new_cell);
			}
		}
	}
}

void IslandGenerateHill(Island *island, int cell_index, Pos hill_origin, int base_radius, int height){
	Pos layer_origin = hill_origin;
	Pos layer_size = { base_radius*2, base_radius*2, 1};
	for( hill_origin.z; hill_origin.z<height; hill_origin.z++ ){
		if(( layer_size.y <= 0) && (layer_size.x <= 0) )
			return;
		IslandGenerateLayer(island, cell_index, hill_origin, layer_size);
		layer_size.y --;
		layer_size.x --;
	}
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
		RotateCamera(island->camera, *island->camera_rotate_key, 20);		//MAGIC NUMBER
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
