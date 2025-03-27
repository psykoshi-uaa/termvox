#include <curses.h>
#include "../include/defines.h"

void InitColors(){
	init_pair(V_V, COLOR_BLACK, COLOR_BLACK);
	init_pair(R_V, COLOR_RED, COLOR_BLACK);
	init_pair(G_V, COLOR_GREEN, COLOR_BLACK);
	init_pair(B_V, COLOR_BLUE, COLOR_BLACK);
	init_pair(Y_V, COLOR_YELLOW, COLOR_BLACK);
	init_pair(M_V, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(C_V, COLOR_CYAN, COLOR_BLACK);
	init_pair(W_V, COLOR_WHITE, COLOR_BLACK);

	init_pair(V_R, COLOR_BLACK, COLOR_RED);
	init_pair(R_R, COLOR_RED, COLOR_RED);
	init_pair(G_R, COLOR_GREEN, COLOR_RED);
	init_pair(B_R, COLOR_BLUE, COLOR_RED);
	init_pair(Y_R, COLOR_YELLOW, COLOR_RED);
	init_pair(M_R, COLOR_MAGENTA, COLOR_RED);
	init_pair(C_R, COLOR_CYAN, COLOR_RED);
	init_pair(W_R, COLOR_WHITE, COLOR_RED);

	init_pair(V_G, COLOR_BLACK, COLOR_GREEN);
	init_pair(R_G, COLOR_RED, COLOR_GREEN);
	init_pair(G_G, COLOR_GREEN, COLOR_GREEN);
	init_pair(B_G, COLOR_BLUE, COLOR_GREEN);
	init_pair(Y_G, COLOR_YELLOW, COLOR_GREEN);
	init_pair(M_G, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(C_G, COLOR_CYAN, COLOR_GREEN);
	init_pair(W_G, COLOR_WHITE, COLOR_GREEN);

	init_pair(V_B, COLOR_BLACK, COLOR_BLUE);
	init_pair(R_B, COLOR_RED, COLOR_BLUE);
	init_pair(G_B, COLOR_GREEN, COLOR_BLUE);
	init_pair(B_B, COLOR_BLUE, COLOR_BLUE);
	init_pair(Y_B, COLOR_YELLOW, COLOR_BLUE);
	init_pair(M_B, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(C_B, COLOR_CYAN, COLOR_BLUE);
	init_pair(W_B, COLOR_WHITE, COLOR_BLUE);

	init_pair(V_Y, COLOR_BLACK, COLOR_YELLOW);
	init_pair(R_Y, COLOR_RED, COLOR_YELLOW);
	init_pair(G_Y, COLOR_GREEN, COLOR_YELLOW);
	init_pair(B_Y, COLOR_BLUE, COLOR_YELLOW);
	init_pair(Y_Y, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(M_Y, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(C_Y, COLOR_CYAN, COLOR_YELLOW);
	init_pair(W_Y, COLOR_WHITE, COLOR_YELLOW);

	init_pair(V_M, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(R_M, COLOR_RED, COLOR_MAGENTA);
	init_pair(G_M, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(B_M, COLOR_BLUE, COLOR_MAGENTA);
	init_pair(Y_M, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(M_M, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(C_M, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(W_M, COLOR_WHITE, COLOR_MAGENTA);

	init_pair(V_C, COLOR_BLACK, COLOR_CYAN);
	init_pair(R_C, COLOR_RED, COLOR_CYAN);
	init_pair(G_C, COLOR_GREEN, COLOR_CYAN);
	init_pair(B_C, COLOR_BLUE, COLOR_CYAN);
	init_pair(Y_C, COLOR_YELLOW, COLOR_CYAN);
	init_pair(M_C, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(C_C, COLOR_CYAN, COLOR_CYAN);
	init_pair(W_C, COLOR_WHITE, COLOR_CYAN);

	init_pair(V_W, COLOR_BLACK, COLOR_WHITE);
	init_pair(R_W, COLOR_RED, COLOR_WHITE);
	init_pair(G_W, COLOR_GREEN, COLOR_WHITE);
	init_pair(B_W, COLOR_BLUE, COLOR_WHITE);
	init_pair(Y_W, COLOR_YELLOW, COLOR_WHITE);
	init_pair(M_W, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(C_W, COLOR_CYAN, COLOR_WHITE);
	init_pair(W_W, COLOR_WHITE, COLOR_WHITE);
}
