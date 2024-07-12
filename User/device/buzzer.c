#include "buzzer.h"
#include "User/task/task.h"
#include "User/task/timed.h"
#include "ti_msp_dl_config.h"

void buzzer_set(uint8_t sta)
{
    if(sta == 1)
    {
        DL_GPIO_clearPins(BUZZER_PORT_PORT, BUZZER_PORT_BUZZER_PIN_PIN);
    }
    else {
        DL_GPIO_setPins(BUZZER_PORT_PORT, BUZZER_PORT_BUZZER_PIN_PIN);
    }
}

void buzzer_on(void *para);
void buzzer_off(void *para);

void buzzer_off(void *para)
{
    buzzer_set(0);

    para--;
    if(((uint32_t)para & 0xff) == 0)
        return;
    uint32_t off_time = ((uint32_t)para >> 16) & 0xff;

    Task T = task_new(buzzer_on, para);
    task_timed_insert(&task.timed, T, off_time);
}

void buzzer_on(void *para)
{
    buzzer_set(1);

    uint32_t on_time = ((uint32_t)para >> 8) & 0xff;

    Task T = task_new(buzzer_off, para);
    task_timed_insert(&task.timed, T, on_time);
}

void buzzer_buzz(uint8_t start_time, uint8_t times, uint8_t on_time, uint8_t off_time)
{

    buzzer_set(0);

    if(times == 0)
        return;
    
    uint32_t para = (off_time << 16) | (on_time << 8) | times;

    Task T = task_new(buzzer_on, (void *)para);
    task_timed_insert(&task.timed, T, start_time);
}


