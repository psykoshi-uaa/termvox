#include "../include/numanip.h"

void IncInt(int* num, int max){
	if( *num < max )
		*num++;
}

void DecrInt(int* num, int min){
	if( *num > min )
		*num--;
}

void IncIntLoop(int* num, int min, int max){
	if( *num < max )
		*num++;
	else
		*num = min;
}

void DecrIntLoop(int* num, int min, int max){
	if( *num > min )
		*num--;
	else
		*num = max;
}
