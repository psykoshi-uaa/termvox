#include <stdlib.h>
#include <math.h>
#include "../include/camera.h"
#include "../include/pos.h"
#include "../include/input.h"

Camera InitCamera(){
	Camera init_camera;
	Pos cam_origin = { 0, 0, 10 };
	init_camera.origin = cam_origin;
	init_camera.rotation = 0.0f;
	return init_camera;
}

void FreeCamera(Camera* camera){
	if( camera != NULL ){
		free(camera);
		camera = NULL;
	}
}

void SetCameraPos(Camera* camera, int y, int x, int z){
	camera->origin.y = y;
	camera->origin.x = x;
	camera->origin.z = z;
}

void TranslateCamera(Camera* camera, MoveKeys translate_key, MoveKeys vert_key){
	camera->origin.y += translate_key.down.is_pressed - translate_key.up.is_pressed;
	camera->origin.x += translate_key.right.is_pressed - translate_key.left.is_pressed;
	camera->origin.z += vert_key.down.is_pressed - vert_key.up.is_pressed;
}

void RotateCamera(Camera* camera, MoveKeys rotate_key, float scale){
	int dir = rotate_key.left.is_pressed - rotate_key.right.is_pressed;
	camera->rotation += dir / scale;
	if( camera->rotation <= 0)
		camera->rotation = 2*M_PI;
	else if( camera->rotation >= 2*M_PI)
		camera->rotation = 0;
	//camera->rotation = floor(camera->rotation / scale);
	//camera->rotation *= scale;
}

