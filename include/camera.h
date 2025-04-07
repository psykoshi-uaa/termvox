#ifndef CAMERA_H
#define CAMERA_H
#include <stdlib.h>
#include "pos.h"
#include "input.h"

struct Camera {
	Pos origin;
	float rotation;
} typedef Camera;

Camera InitCamera();
void SetCameraPos(Camera* camera, int y, int x, int z);
void TranslateCamera(Camera* camera, MoveKeys translate_key, MoveKeys vert_key);
void RotateCamera(Camera* camera, MoveKeys rotate_key, float scale);
//void FreeCamera(Camera* camera);
#endif
