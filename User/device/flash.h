#ifndef __FLASH_H__
#define __FLASH_H__

#include "stdint.h"

void flash_erase(unsigned sector);
void flash_write(unsigned sector, const void *src, unsigned len);
void flash_write_to(unsigned sector, unsigned position, const void *src,
                    unsigned len);
void flash_write_u64(unsigned sector, unsigned index, uint32_t DA, uint32_t TA);
void flash_read(unsigned sector, void *dest, unsigned len);
const void *flash_use(unsigned sector);

#endif // !__FLASH_H__
