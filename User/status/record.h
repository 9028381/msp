#ifndef __RECORD_H__
#define __RECORD_H__

void status_record(int var);
void status_record_force_swap_mem();

void record_once_switch(unsigned short var, void *para);
void repeat_open(unsigned short var, void *para);

#endif // !__RECORD_H__
