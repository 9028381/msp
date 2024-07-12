#include "sl.h"
#include "User/task/task.h"
#include "User/task/timed.h"
#include <sys/_stdint.h>

uint16_t num[2] = {1,1};
uint8_t i = 0;


void print_sl(void *para)
{
    uint8_t count = (uint32_t)para & 0xff;
    if(count == 0)
        return;
    
    PRINTLN("%d", num[i++]);
    num[i-1] = num[0] + num[1];
    
    i = i%2;
    para--;
    Task T = task_new(print_sl, para);
    task_timed_insert(&task.timed, T, num[i]);
    
}

void print_start(uint8_t times)
{
    uint32_t para = times;
    print_sl((void *)para);
}