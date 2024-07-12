#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "stdint.h"

void buzzer_ring();
void buzzer_mute();

void buzzer_blame(uint8_t later_start, uint8_t times, uint8_t ring_time,
                  uint8_t mute_time);

#endif // !__BUZZER_H__
