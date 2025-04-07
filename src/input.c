#include <curses.h>
#include "../include/input.h"

char GetCharInput(int argn, ...){
	char user_inp;
	while( true ){
		user_inp = getch();
		va_list args;
		va_start(args, argn);
		for( int c=0; c<argn; c++ ){
			if( user_inp == va_arg(args, int) ){
				va_end(args);
				return user_inp;
			}
		}
	}
}

Keybind InitKeybind(char key){
	Keybind init_keybind;
	init_keybind.key = key;
	init_keybind.is_pressed = 0;
	return init_keybind;
}

MoveKeys InitMoveKeys(char up, char down, char left, char right){
	MoveKeys init_move_keys;
	init_move_keys.up = InitKeybind(up);
	init_move_keys.down = InitKeybind(down);
	init_move_keys.left = InitKeybind(left);
	init_move_keys.right = InitKeybind(right);
	return init_move_keys;
}
/*
void FreeKeybind(Keybind* keybind){
	if( keybind != NULL ){
		free(keybind);
		keybind = NULL;
	}
}

void FreeMoveKeys(MoveKeys* move_keys){
	if( move_keys != NULL ){
		FreeKeybind(move_keys->up);
		FreeKeybind(move_keys->down);
		FreeKeybind(move_keys->left);
		FreeKeybind(move_keys->right);
		free(move_keys);
		move_keys = NULL;
	}
}
*/

void UpdateMoveKeys(MoveKeys* move_keys, char key_pressed){
	if( key_pressed == move_keys->up.key)
		move_keys->up.is_pressed = 1;
	else
		move_keys->up.is_pressed = 0;

	if( key_pressed == move_keys->down.key)
		move_keys->down.is_pressed = 1;
	else
		move_keys->down.is_pressed = 0;

	if( key_pressed == move_keys->left.key)
		move_keys->left.is_pressed = 1;
	else
		move_keys->left.is_pressed = 0;

	if( key_pressed == move_keys->right.key)
		move_keys->right.is_pressed = 1;
	else
		move_keys->right.is_pressed = 0;
}
