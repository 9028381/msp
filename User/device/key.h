#ifndef __KEY_H_
#define __KEY_H_

#include "stdint.h"
#include "../drive/gpio.h"
#include "stdbool.h"

enum KEY
{
    KEY1,
    KEY2,
};

bool get_button_sta(enum KEY witch);
void keyboard_init();

#endif
