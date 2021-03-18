#include "main.h"
#include "control.h"
#include "lost_count.h"

#define lost_threshold_value 100

int lost_check=0;

void LostCountAdd(uint16_t*count)
{
	if(*count<0xFFFE) (*count)++;
}

void FeedDog(uint16_t*count)
{
    *count=0;
}

uint16_t LostChecker(uint16_t* count,int* statu,const uint16_t cycle)
{
    if(count>lost_threshold_value*cycle)
		*statu=1;
	else
		*statu=0;
	return *statu;
}



