#include "key.h"
#include "User/task/task.h"
#include "ti_msp_dl_config.h"
#include "User/status/status.h"
#include "User/utils/log.h"

bool get_button_sta(enum KEY witch)
{
    if(witch == KEY1)
    {
        return !(bool)DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN);
    }
    else if(witch == KEY2)
    {
        return !(bool)DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN);
    }
}

void key_react(void *para){
    static bool sta=true;
    static unsigned int con = 0;
    bool key1 = get_button_sta(KEY1);
    con = con <<1 + key1;

    if (key1&&!con) {
        if (sta){
            PRINTLN("info: start record");
            status.mode.record = true;
            status.mode.repeat = false;
        }else {
            PRINTLN("info: start repeat");
            status.mode.record = false;
            status.mode.repeat = true;
        }
        status.times = 0;
        sta = !sta;
    }

    keyboard_init();
}

void keyboard_init(){
    Task t = task_new(key_react, NULL);
    task_timed_append(&task.timed, t, 2);
}