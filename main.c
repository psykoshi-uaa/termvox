#include <stdlib.h>
#include <curses.h>
#include "include/defines.h"
#include "include/pos.h"
#include "include/input.h"
#include "include/cell.h"
#include "include/island.h"

enum STATE {GENERATE, SIM, EXIT} typedef STATE;

void InitCurses();
void ScreenWipe();
void MainStateMachine(STATE* cur_state, char* user_inp, Island* island);

int main(){
	InitCurses();
	InitColors();
	halfdelay(1);

	STATE cur_state = GENERATE;
	char user_inp = ' ';
	
	Pos island_origin = { 0 };
	Island island = InitIsland(island_origin);

	while( cur_state != EXIT ){
		MainStateMachine(&cur_state, &user_inp, &island);
	}

	FreeIsland(&island);
	endwin();
	return 0;
}

void MainStateMachine(STATE* cur_state, char* user_inp, Island* island){
	switch( *cur_state ){
	case GENERATE:
		IslandGenerateLand(island);
		IslandUpdateTimeOfDay(island);
		*cur_state = SIM;
		break;
	case SIM:
		ScreenWipe();
		IslandEngine(island, *user_inp);
		PrintIslandDebug(*island);
		*user_inp = GetCharInput(10, 'q', ' ',
			island->camera_translate_key.up.key, island->camera_translate_key.down.key,
			island->camera_translate_key.left.key, island->camera_translate_key.right.key,
			island->camera_rotate_key.up.key, island->camera_rotate_key.down.key,
			island->camera_rotate_key.left.key, island->camera_rotate_key.right.key
		);
		if( *user_inp == 'q' )
			*cur_state = EXIT;
		if( *user_inp == ' ' )
			IslandUpdateTimeOfDay(island);
		break;
	default:
		break;
	}
}

void InitCurses(){
	initscr();
	start_color();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
}

void ScreenWipe(){
	int screensize_h;
	int screensize_w;
	getmaxyx(stdscr, screensize_h, screensize_w);
	char* screenline[screensize_h * screensize_w];
	for( int y=0; y<screensize_h; y++ ){
		for( int x=0; x<screensize_h; x++ ){
			*screenline[(y*screensize_h) + x] = 'X';
		if( x == screensize_w )
			*screenline[(y*screensize_h) + x] = '\n';
		}
	}

	//char word = 'w\nw';
	mvprintw(0, 0, "%s", screenline);
}
