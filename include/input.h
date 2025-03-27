#ifndef INPUT_H
#define INPUT_H
#include <stdlib.h>

struct Keybind {
	char key;
	int is_pressed;
} typedef Keybind; 

struct MoveKeys {
	Keybind* up;
	Keybind* down;
	Keybind* left;
	Keybind* right;
} typedef MoveKeys;

char GetCharInput(int argn, ...);
Keybind* InitKeybind(char key);
MoveKeys* InitMoveKeys(char up, char down, char left, char right);
void FreeKeybind(Keybind* key);
void FreeMoveKeys(MoveKeys* move_keys);
void UpdateMoveKeys(MoveKeys* move_keys, char key_pressed);
#endif
